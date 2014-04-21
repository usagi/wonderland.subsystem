#pragma once

#include <cassert>
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
      
      class joystick_states_t
      {
        friend class subsystem_base_t;
        
      public:
        using digitals_t = std::vector<bool>;
        using analogs_t  = std::vector<double>;
        using balls_t    = std::vector<glm::vec2>;
        using hats_t     = std::vector<glm::vec2>;
        using name_t     = std::string;
        
      private:
        digitals_t _digitals;
        analogs_t  _analogs;
        balls_t    _balls;
        hats_t     _hats;
        name_t     _name;
        
        auto clear()
          -> void
        {
          _digitals.clear();
          _analogs.clear();
        }
        
      public:
        
        auto digitals() const
          -> const digitals_t&
        { return _digitals; }
        
        auto analogs() const
          -> const analogs_t&
        { return _analogs; }
        
        auto balls() const
          -> const balls_t&
        { return _balls; }
        
        auto hats() const
          -> const hats_t&
        { return _hats; }
        
        auto size_of_digitals() const
          -> unsigned
        { return _digitals.size(); }
        
        auto size_of_analogs() const
          -> unsigned
        { return _analogs.size(); }
        
        auto digital(unsigned index) const
          -> bool
        { return _digitals.at(index); }
        
        auto analog(unsigned index) const
          -> double
        { return _analogs.at(index); }
        
        auto ball(unsigned index) const
          -> const glm::vec2&
        { return _balls.at(index); }
        
        auto hats(unsigned index) const
          -> const glm::vec2&
        { return _hats.at(index); }
        
        auto name() const
          -> std::string
        { return _name; }
        
      };
      
      namespace initialize_params
      {
        namespace client_api
        {
          constexpr auto opengl   = "opengl";
          constexpr auto opengles = "opengl_es";
        };
        
        namespace context_robustness
        {
          constexpr auto no_robustness         = "no_robustness";
          constexpr auto no_reset_notification = "no_reset_notification";
          constexpr auto lose_context_on_reset = "lose_context_on_reset";
        };
        
        namespace opengl_profile
        {
          constexpr auto any    = "any";
          constexpr auto compat = "compat";
          constexpr auto core   = "core";
        };
      }
      
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
          
        using joysticks_states_t
          = std::vector<joystick_states_t>;
          
      protected:
        
        keyboard_states_t _keyboard_states;
        pointing_states_t _pointing_states;
        joysticks_states_t _joysticks_states;
        
        bool _to_continue;
        
        // write functions
        
        //   keyboard
        virtual auto keyboard_state(key_code_t keycode, bool action)
          -> void
        { _keyboard_states[keycode] = action; }
        
        //   pointing
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
        
        //   joystick
        virtual auto joysticks_resize_by_index(const unsigned index_of_joystick)
          -> void
        {
          if ( index_of_joystick >= _joysticks_states.size() )
            _joysticks_states.resize( index_of_joystick + 1 );
        }
        
        virtual auto joystick_digital_resize_by_index(const unsigned index_of_joystick ,const unsigned index_of_digital)
          -> void
        {
          joysticks_resize_by_index(index_of_joystick);
          
          if ( index_of_digital >= _joysticks_states[index_of_joystick]._digitals.size() )
            _joysticks_states[index_of_joystick]._digitals.resize( index_of_digital + 1 );
        }
        
        virtual auto joystick_analog_resize_by_index(const unsigned index_of_joystick ,const unsigned index_of_analog)
          -> void
        {
          joysticks_resize_by_index(index_of_joystick);
          
          if ( index_of_analog >= _joysticks_states[index_of_joystick]._analogs.size() )
            _joysticks_states[index_of_joystick]._analogs.resize( index_of_analog + 1 );
        }
        
        virtual auto joystick_ball_resize_by_index(const unsigned index_of_joystick ,const unsigned index_of_ball)
          -> void
        {
          joysticks_resize_by_index(index_of_joystick);
          
          if ( index_of_ball >= _joysticks_states[index_of_joystick]._balls.size() )
            _joysticks_states[index_of_joystick]._balls.resize( index_of_ball + 1 );
        }
        
        virtual auto joystick_hat_resize_by_index(const unsigned index_of_joystick ,const unsigned index_of_hat)
          -> void
        {
          joysticks_resize_by_index(index_of_joystick);
          
          if ( index_of_hat >= _joysticks_states[index_of_joystick]._hats.size() )
            _joysticks_states[index_of_joystick]._hats.resize( index_of_hat + 1 );
        }
        
        virtual auto joystick_states(const unsigned index_of_joystick, const joystick_states_t& j )
          -> void
        { 
          joysticks_resize_by_index(index_of_joystick);
          _joysticks_states[index_of_joystick] = j;
        }
        
        virtual auto joystick_states(const unsigned index_of_joystick, joystick_states_t&& j )
          -> void
        {
          joysticks_resize_by_index(index_of_joystick);
          _joysticks_states.at(index_of_joystick) = std::move(j);
        }
        
        virtual auto joystick_state_digital(const unsigned index_of_joystick, const unsigned index_of_digital, const bool action)
          -> void
        {
          joystick_digital_resize_by_index(index_of_joystick, index_of_digital);
          _joysticks_states[index_of_joystick]._digitals[index_of_digital] = action;
        }
        
        virtual auto joystick_state_analog(const unsigned index_of_joystick, const unsigned index_of_analog, const double snorm_value)
          -> void
        {
          assert(snorm_value >= -1 and snorm_value <= 1);
          joystick_analog_resize_by_index(index_of_joystick, index_of_analog);
          _joysticks_states[index_of_joystick]._analogs[index_of_analog] = snorm_value;
        }
        
        virtual auto joystick_state_name(const unsigned number_of_joystick, const std::string& name)
          -> void
        {
          joysticks_resize_by_index(number_of_joystick);
          _joysticks_states[number_of_joystick]._name = name;
        }
        
        virtual auto joystick_state_ball(const unsigned index_of_joystick, const unsigned index_of_ball, const glm::vec2& value)
          -> void
        {
          joystick_ball_resize_by_index(index_of_joystick, index_of_ball);
          _joysticks_states[index_of_joystick]._balls[index_of_ball] = value;
        }
        
        virtual auto joystick_state_ball(const unsigned index_of_joystick, const unsigned index_of_ball, glm::vec2&& value)
          -> void
        {
          joystick_ball_resize_by_index(index_of_joystick, index_of_ball);
          _joysticks_states[index_of_joystick]._balls[index_of_ball] = std::move(value);
        }
        
        virtual auto joystick_state_hat(const unsigned index_of_joystick, const unsigned index_of_hat, const glm::vec2& value)
          -> void
        {
          joystick_hat_resize_by_index(index_of_joystick, index_of_hat);
          _joysticks_states[index_of_joystick]._hats[index_of_hat] = value;
        }
        
        virtual auto joystick_state_hat(const unsigned index_of_joystick, const unsigned index_of_hat, glm::vec2&& value)
          -> void
        {
          joystick_hat_resize_by_index(index_of_joystick, index_of_hat);
          _joysticks_states[index_of_joystick]._hats[index_of_hat] = std::move(value);
        }
        
        virtual auto joystick_state_name(const unsigned number_of_joystick, std::string&& name)
          -> void
        {
          joysticks_resize_by_index(number_of_joystick);
          _joysticks_states[number_of_joystick]._name = std::move(name);
        }
        
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
        
        //   keyboard
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
        
        //   pointing
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
        
        //   joystick
        virtual auto joysticks_states() const
          -> const joysticks_states_t&
        { return _joysticks_states; }
        
        virtual auto joystick_states(const unsigned index) const
          -> const joystick_states_t
        { return _joysticks_states.at(index); }
        
        virtual auto joystick_state_digital(const unsigned index_of_joystick, const unsigned index_of_digital) const
          -> const bool
        { return _joysticks_states.at(index_of_joystick)._digitals.at(index_of_digital); }
        
        virtual auto joystick_state_analog(const unsigned index_of_joystick, const unsigned index_of_analog) const
          -> const double
        { return _joysticks_states.at(index_of_joystick)._analogs.at(index_of_analog); }
        
        virtual auto joystick_state_axes2_from_analogs
        ( const unsigned index_of_joystick
        , const unsigned index_x_of_analog
        , const unsigned index_y_of_analog
        ) const
          -> const glm::vec2
        {
          const auto& j = _joysticks_states.at( index_of_joystick );
          return
          { j._analogs.at( index_x_of_analog )
          , j._analogs.at( index_y_of_analog )
          };
        }
        
        virtual auto joystick_state_axes2_from_analogs
        ( const unsigned index_of_joystick
        , const unsigned index_x_of_analog
        ) const
          -> const glm::vec2
        {
          return joystick_state_axes2_from_analogs
                 ( index_of_joystick
                 , index_x_of_analog
                 , index_x_of_analog + 1
                 );
        }
        
        virtual auto joystick_state_axes3_from_analogs
        ( const unsigned index_of_joystick
        , const unsigned index_x_of_analog
        , const unsigned index_y_of_analog
        , const unsigned index_z_of_analog
        ) const
          -> const glm::vec3
        {
          const auto& j = _joysticks_states.at( index_of_joystick );
          return
          { j._analogs.at( index_x_of_analog )
          , j._analogs.at( index_y_of_analog )
          , j._analogs.at( index_z_of_analog )
          };
        }
        
        virtual auto joystick_state_axes3_from_analogs
        ( const unsigned index_of_joystick
        , const unsigned index_x_of_analog
        , const unsigned index_y_of_analog
        ) const
          -> const glm::vec3
        {
          return joystick_state_axes3_from_analogs
                 ( index_of_joystick
                 , index_x_of_analog
                 , index_y_of_analog
                 , index_y_of_analog + 1
                 );
        }
        
        virtual auto joystick_state_axes3_from_analogs
        ( const unsigned index_of_joystick
        , const unsigned index_x_of_analog
        ) const
          -> const glm::vec3
        {
          return joystick_state_axes3_from_analogs
                 ( index_of_joystick
                 , index_x_of_analog
                 , index_x_of_analog + 1
                 , index_x_of_analog + 2
                 );
        }
        
        virtual auto joystick_state_ball(const unsigned index_of_joystick, const unsigned index_of_ball) const
          -> const glm::vec2&
        { return _joysticks_states.at(index_of_joystick)._balls.at(index_of_ball); }
        
        virtual auto joystick_state_hat(const unsigned index_of_joystick, const unsigned index_of_hat) const
          -> const glm::vec2&
        { return _joysticks_states.at(index_of_joystick)._hats.at(index_of_hat); }
        
        virtual auto joystick_name( const unsigned index_of_joystick)
          -> const std::string&
        { return _joysticks_states.at(index_of_joystick)._name; }
        
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