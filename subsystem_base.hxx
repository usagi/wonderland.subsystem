#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>
#include <memory>
#include <unordered_map>
#include <forward_list>
#include <vector>

#include <boost/property_tree/ptree.hpp>
#include <boost/optional.hpp>

namespace wonder_rabbit_project
{
  namespace wonderland
  {
    namespace subsystem
    {
      struct subsystem_runtime_error_t
        : std::runtime_error
      {
        subsystem_runtime_error_t(const std::string& what)
          : std::runtime_error(what)
        { }
      };
      
      struct version_t
      {
        std::uint16_t major, minor, revision;
        
        auto to_string() -> std::string
        {
          return std::to_string(major) + "."
               + std::to_string(minor) + "."
               + std::to_string(revision)
            ;
        }
      };
      
      class subsystem_base_t
        : public std::enable_shared_from_this<subsystem_base_t>
      {
      public:
        
        using initialize_param_key_t
          = std::string;
          
        using initialize_param_value_t
          = boost::any;
          
        using initialize_params_t
          = boost::property_tree::ptree;
            
        using update_functors_t
          = std::forward_list
            < std::function<void()>
            >;
        
        using render_functors_t
          = update_functors_t;
          
        using keyboard_states_t
          = std::vector<bool>;
          
      protected:
        
        keyboard_states_t _keyboard_states;
        bool _to_continue;
        
      public:
        
        update_functors_t update_functors;
        render_functors_t render_functors;
        
        subsystem_base_t()
        {
          _keyboard_states.resize( std::numeric_limits<key_code_t>::max() );
        }
        
        virtual ~subsystem_base_t() { }
        
        virtual auto default_initialize_params() const
          -> initialize_params_t
        { return initialize_params_t(); }
        
        virtual auto initialize(initialize_params_t&&) -> void { }
        
        virtual auto before_update() -> void { }
        virtual auto after_update()  -> void { }
        virtual auto before_render() -> void { }
        virtual auto after_render()  -> void { }
        virtual auto version() const -> version_t = 0;
        virtual auto name()    const -> std::string = 0;
        
        virtual auto update() -> void
        {
          for ( const auto& f : update_functors )
            f();
        }
        
        virtual auto render() -> void
        {
          for ( const auto& f : render_functors )
            f();
        }
        
        virtual auto to_continue() const
          -> bool
        { return _to_continue; }
        
        virtual auto to_continue(const bool b)
          -> void
        { _to_continue = b; }
        
        template<key_code_t T_keycode>
        inline auto keyboard_state() const 
          -> bool
        {
          static_assert(T_keycode >= std::numeric_limits<key_code_t>::min(), "T_keycode must: T_keycode >= std::numeric_limits<key_code_t>::min()");
          static_assert(T_keycode <= std::numeric_limits<key_code_t>::max(), "T_keycode must: T_keycode <= std::numeric_limits<key_code_t>::max()");
          return _keyboard_states[key_code_t(T_keycode)];
        }
        
        virtual auto keyboard_state(key_code_t keycode) const
          -> bool
        { return _keyboard_states[keycode]; }
        
        virtual auto keyboard_state(key_code_t keycode, bool action)
          -> void
        { _keyboard_states[keycode] = action; }
        
        virtual auto keyboard_states() const
          -> const keyboard_states_t&
        { return _keyboard_states; }
        
        virtual auto invoke()
          -> void
        {
          _to_continue = true;
#ifdef EMSCRIPTEN  
          emscripten_set_main_loop( []
#else
          do
#endif
          {
            before_update();
            update();
            after_update();

            before_render();
            render();
            after_render();
          }
#ifdef EMSCRIPTEN  
          , 0, 1);
#else
          while ( to_continue() );
#endif
        }
        
      };
      
    }
  }
}