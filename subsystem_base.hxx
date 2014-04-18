#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>
#include <memory>
#include <unordered_map>
#include <forward_list>
#include <vector>
#include <mutex>

#include <boost/property_tree/ptree.hpp>

// https://github.com/g-truc/glm
#include <glm/glm.hpp>

#ifdef EMSCRIPTEN
namespace
{
  static std::mutex emscripten_main_loop_mutex;
}
#endif

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
      
      class pointing_states_t
      {
      public:
        friend class subsystem_base_t;
        
        static constexpr std::uint_fast8_t number_of_buttons = 8;
        
        using buttons_t  = std::vector<bool>;
        using wheel_t    = glm::vec2;
        using position_t = glm::vec2;
        
      private:
        buttons_t  _buttons;
        wheel_t    _wheel;
        position_t _position;
        
      public:
        
        explicit pointing_states_t()
          : _buttons(number_of_buttons)
        { }
        
        template<unsigned T_button_number>
        auto button() const
          -> bool
        {
          static_assert(T_button_number < number_of_buttons, "must T_button_number < number_of_buttons");
          return _buttons[T_button_number];
        }
        
        auto button(unsigned button_number) const
          -> bool
        { return _buttons.at(button_number); }
        
        auto wheel() const
          -> const wheel_t&
        { return _wheel; }
        
        auto position() const
          -> const position_t&
        { return _position; }
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
        pointing_states_t _pointing_states;
        bool _to_continue;
        
        // write functions
        
        virtual auto keyboard_state(key_code_t keycode, bool action)
          -> void
        { _keyboard_states[keycode] = action; }
        
        virtual auto pointing_states(pointing_states_t&& ps)
          -> void
        { _pointing_states = std::move( ps ); }
        
        template <unsigned T_button_number>
        auto pointing_states_button(const bool action)
          -> void
        {
          static_assert(T_button_number < pointing_states_t::number_of_buttons, "must T_button_number < pointing_states_t::number_of_buttons");
          _pointing_states._buttons[T_button_number] = action;
        }
        
        virtual auto pointing_states_button(const unsigned button_number, const bool action)
          -> void
        { _pointing_states._buttons.at(button_number) = action; }
        
        virtual auto pointing_states_wheel(const pointing_states_t::wheel_t& wheel)
          -> void
        { _pointing_states._wheel = wheel; }
        
        virtual auto pointing_states_wheel(pointing_states_t::wheel_t&& wheel)
          -> void
        { _pointing_states._wheel = std::move(wheel); }
        
        virtual auto pointing_states_position(const pointing_states_t::position_t& position)
          -> void
        { _pointing_states._position = position; }
        
        virtual auto pointing_states_position(pointing_states_t::position_t&& position)
          -> void
        { _pointing_states._position = std::move(position); }
        
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
        
        // read functions
        
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
        
        virtual auto keyboard_states() const
          -> const keyboard_states_t&
        { return _keyboard_states; }
        
        virtual auto pointing_states() const
          -> const pointing_states_t&
        { return _pointing_states; }
        
        template <unsigned T_button_number>
        auto pointing_states_button() const
          -> bool
        { return _pointing_states.button<T_button_number>(); }
        
        virtual auto pointing_states_button(const unsigned button_number) const
          -> bool
        { return _pointing_states.button(button_number); }
        
        virtual auto pointing_states_wheel() const
          -> const pointing_states_t::wheel_t&
        { return _pointing_states.wheel(); }
        
        virtual auto pointing_states_position() const
          -> const pointing_states_t::position_t&
        { return _pointing_states.position(); }
        
        virtual auto invoke()
          -> void
        {
          _to_continue = true;
#ifdef EMSCRIPTEN
          if( not ::emscripten_main_loop_mutex.try_lock() )
            throw subsystem_runtime_error_t( "::emscripten_main_loop_mutex cannot lock" );
          
          emscripten_set_main_loop_arg( [](void* arg)
          {
            auto this_ = reinterpret_cast<subsystem_base_t*>(arg);
            this_ -> invoke_step();
            if ( not this_ -> to_continue() )
            {
              emscripten_cancel_main_loop();
              ::emscripten_main_loop_mutex.unlock();
            }
          }
          , this, 0, 1);
#else
          do
            invoke_step();
          while ( to_continue() );
#endif
        }
        
        virtual auto invoke_step() -> void
        {
          before_update();
          update();
          after_update();

          before_render();
          render();
          after_render();
        }
        
      };
      
    }
  }
}