#pragma once

#include <forward_list>
#include <unordered_map>
#include <limits>
#include <cstdint>

#include <GLFW/glfw3.h>

#include "subsystem_base.hxx"

namespace
{
  using window_owner_dictionary_t = std::unordered_map
    < GLFWwindow*
    , std::weak_ptr<wonder_rabbit_project::wonderland::subsystem::subsystem_base_t>
    >;
    
  auto window_owner_dictionary = std::make_shared<window_owner_dictionary_t>();
}

namespace wonder_rabbit_project
{
  namespace wonderland
  {
    namespace subsystem
    {
      struct glfw3_runtime_error_t
        : subsystem_runtime_error_t
      {
        glfw3_runtime_error_t(const std::string& what)
          : subsystem_runtime_error_t(what)
        { }
      };
      
      class GLFW3_t
        : public subsystem_base_t
      {
        using dtor_hook_t  = std::function<void()>;
        using dtor_hooks_t = std::forward_list<dtor_hook_t>;
        
        dtor_hooks_t _dtor_hooks;
        
        GLFWwindow* _window;
        
      public:
        pointing_states_t::wheel_t temporary_wheel;
        
      private:
        
        auto initialize_glfw() -> void
        {
          const auto r = glfwInit();
          if ( not r )
            throw glfw3_runtime_error_t( std::string("glfwInit failed. return value: ") + std::to_string(r) );
          
          _dtor_hooks.emplace_front( []{ glfwTerminate(); } );
        }
        
        auto initialize_set_error_callback() const -> void
        {
          glfwSetErrorCallback
          ( [](int error, const char* description)
            { throw glfw3_runtime_error_t
              ( std::string("glfw error: error = ") + std::to_string(error) 
              + std::string(" , description = ") + std::string(description)
              );
            }
          );
        }
        
        auto initialize_window_hints(initialize_params_t& ps) -> void
        {
          initialize_params_t dps;
          default_initialize_params_window_hints(dps);
          
          const auto get = [&ps, &dps](const char* name)
          { return ps.get(name, dps.get<int>(name)); };
          
          const auto get_bool_as_int = [&ps, &dps](const char* name)
          { return int(ps.get(name, dps.get<bool>(name))); };
          
          const auto get_string = [&ps, &dps](const char* name)
          { return ps.get(name, dps.get<std::string>(name)); };
          
          glfwWindowHint( GLFW_RESIZABLE , get_bool_as_int("resizable") );
          glfwWindowHint( GLFW_VISIBLE   , get_bool_as_int("visible" ) );
          glfwWindowHint( GLFW_DECORATED , get_bool_as_int("decorated" ) );
          glfwWindowHint( GLFW_RED_BITS         , get("red_bits" ) );
          glfwWindowHint( GLFW_GREEN_BITS       , get("green_bits" ) );
          glfwWindowHint( GLFW_BLUE_BITS        , get("blue_bits" ) );
          glfwWindowHint( GLFW_ALPHA_BITS       , get("alpha_bits" ) );
          glfwWindowHint( GLFW_DEPTH_BITS       , get("depth_bits" ) );
          glfwWindowHint( GLFW_STENCIL_BITS     , get("stencil_bits" ) );
          glfwWindowHint( GLFW_ACCUM_RED_BITS   , get("accum_red_bits" ) );
          glfwWindowHint( GLFW_ACCUM_GREEN_BITS , get("accum_green_bits" ) );
          glfwWindowHint( GLFW_ACCUM_BLUE_BITS  , get("accum_blue_bits" ) );
          glfwWindowHint( GLFW_ACCUM_ALPHA_BITS , get("accum_alpha_bits" ) );
          glfwWindowHint( GLFW_AUX_BUFFERS      , get("aux_buffers" ) );
          glfwWindowHint( GLFW_SAMPLES          , get("samples" ) );
          glfwWindowHint( GLFW_REFRESH_RATE     , get("refresh_rate" ) );
          glfwWindowHint( GLFW_STEREO           , get_bool_as_int("stereo" ) );
          glfwWindowHint( GLFW_SRGB_CAPABLE     , get_bool_as_int("srgb_capable" ) );
          {
            const auto client_api = get_string( "client_api" );
            if ( client_api == "opengl" )
              glfwWindowHint( GLFW_CLIENT_API, GLFW_OPENGL_API );
            else if ( client_api == "opengl_es" )
              glfwWindowHint( GLFW_CLIENT_API, GLFW_OPENGL_ES_API );
          }
          glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR , get("context_version_major" ) );
          glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR , get("context_version_minor" ) );
          {
            const auto context_robustness = get_string( "context_robustness" );
            if ( context_robustness == "no_robustness" )
              glfwWindowHint( GLFW_CONTEXT_ROBUSTNESS, GLFW_NO_ROBUSTNESS );
            else if ( context_robustness == "no_reset_notification" )
              glfwWindowHint( GLFW_CONTEXT_ROBUSTNESS, GLFW_NO_RESET_NOTIFICATION );
            else if ( context_robustness == "lose_context_on_reset")
              glfwWindowHint( GLFW_CONTEXT_ROBUSTNESS, GLFW_LOSE_CONTEXT_ON_RESET );
          }
          glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT , get_bool_as_int("opengl_forward_compat" ) );
          glfwWindowHint( GLFW_OPENGL_DEBUG_CONTEXT  , get_bool_as_int("opengl_debug_context" ) );
          {
            const auto opengl_profile = get_string( "opengl_profile" );
            if ( opengl_profile == "any" )
              glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE );
            if ( opengl_profile == "compat" )
              glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE );
            if ( opengl_profile == "core" )
              glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
          }
        }
        
        auto initialize_create_window(initialize_params_t& ps) -> void
        {
          initialize_params_t dps;
          default_initialize_params_create_window(dps);
          
          const auto window = _window
            = glfwCreateWindow
              ( ps.get("width" , dps.get<int>("width") )
              , ps.get("height", dps.get<int>("height") )
              , ps.get("title" , dps.get<std::string>("title") ).data()
              , static_cast<GLFWmonitor*>(ps.get("GLFW.monitor", dps.get<void*>("GLFW.monitor")) )
              , static_cast<GLFWwindow* >(ps.get("GLFW.window" , dps.get<void*>("GLFW.window")) )
              );
              
          if ( not window )
            throw glfw3_runtime_error_t
            ( "glfwCreateWindow failed. window is nullptr." );
          
          ::window_owner_dictionary -> emplace( window, shared_from_this() );
          
          auto window_owner_dictionary_ = ::window_owner_dictionary;
          
          _dtor_hooks.emplace_front( [ window, window_owner_dictionary_ ]
          {
            ::window_owner_dictionary -> erase( window );
            glfwDestroyWindow( window );
          });
        }
        
        auto initialize_make_contex_current() const ->void
        { glfwMakeContextCurrent( _window ); }
        
        auto initialize_set_scroll_callback() const -> void
        {
          glfwSetScrollCallback( _window, [](GLFWwindow* window, double xoffset, double yoffset)
          {
            std::dynamic_pointer_cast<wonder_rabbit_project::wonderland::subsystem::GLFW3_t>
            ( ::window_owner_dictionary
                -> at(window)
                  .lock()
            )
              -> temporary_wheel = { std::move(xoffset), std::move(yoffset) };
          } );
        }
        
        auto initialize_set_frame_buffer_size_callback() const -> void
        {
          glfwSetFramebufferSizeCallback
          ( _window
          , [](GLFWwindow* window, int width, int height)
            {
              if ( auto p_glViewport = glfwGetProcAddress("glViewport") )
              {
                using PFNGLVIEWPORT = void(*)(std::int32_t, std::int32_t, std::uint32_t, std::uint32_t);
                auto glViewport = reinterpret_cast< PFNGLVIEWPORT >( p_glViewport );
                glViewport(0, 0, width, height);
              }
// TODO: WHYYYYYYYYYYYYYYYYYYYYYYYYYY MSVC+++++++++++++++++++++++++++++++++++++++++++ WINDOWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWS
#if defined(_MSC_VER)
              if ( auto p_glGetError = glfwGetProcAddress("glGetError") )
              {
                using PFNGLGETERROR = std::uint32_t(*)();
                auto glGetError = reinterpret_cast< PFNGLGETERROR >( p_glGetError );
                auto e = glGetError();
                std::cout << std::to_string( e );
              }
#endif
            }
          );
        }
        
        auto window_position(initialize_params_t ps) const -> void
        {
          initialize_params_t dps;
          default_initialize_params_window_position(dps);
          
          // TODO: support SDL convertible flags
          //   0x1FFF0000: UNDEFINED
          //   0x2FFF0000: CENTERED
          
          glfwSetWindowPos
          ( _window
          , ps.get("x" , dps.get<int>("x") ) & 0x0000FFFF
          , ps.get("y" , dps.get<int>("y") ) & 0x0000FFFF
          );
        }
        
        auto process_input_states() -> void
        {
          process_input_states_keyboard();
          process_input_states_pointing();
          process_input_states_joystick();
        }
        
        auto process_input_states_keyboard() -> void
        {
          for ( int glfw3_key = GLFW_KEY_SPACE; glfw3_key < GLFW_KEY_LAST; ++glfw3_key )
          { 
            const auto action = glfwGetKey( _window, glfw3_key );
            const auto fixed_key = key_code_from_glfw3(glfw3_key);
            keyboard_state( fixed_key, bool( action == GLFW_PRESS ) );
          }
        }
        
        auto process_input_states_pointing() -> void
        {
          pointing_states_button<0>( glfwGetMouseButton( _window, 0) );
          pointing_states_button<1>( glfwGetMouseButton( _window, 1) );
          pointing_states_button<2>( glfwGetMouseButton( _window, 2) );
          pointing_states_button<3>( glfwGetMouseButton( _window, 3) );
          pointing_states_button<4>( glfwGetMouseButton( _window, 4) );
          pointing_states_button<5>( glfwGetMouseButton( _window, 5) );
          pointing_states_button<6>( glfwGetMouseButton( _window, 6) );
          pointing_states_button<7>( glfwGetMouseButton( _window, 7) );
          
          double x, y;
          glfwGetCursorPos( _window, &x, &y );
          pointing_states_position( { std::move(x), std::move(y) } );
          
          pointing_states_wheel( std::move( temporary_wheel ) );
          temporary_wheel = { 0, 0 };
        }
        
        auto process_input_states_joystick() -> void
        {
#ifndef EMSCRIPTEN
          for
          ( int index_of_joystick = 0
          ; glfwJoystickPresent(index_of_joystick) == GL_TRUE
          ; ++index_of_joystick
          )
          {
            { // digitals
              int number_of_elements;
              const auto actions = glfwGetJoystickButtons( index_of_joystick, &number_of_elements );
              if ( actions not_eq nullptr )
                for ( auto index_of_element = 0; index_of_element < number_of_elements; ++index_of_element )
                  joystick_state_digital( index_of_joystick, index_of_element, bool(actions[index_of_element]) );
            }
            { // analogs
              int number_of_elements;
              const auto actions = glfwGetJoystickAxes( index_of_joystick, &number_of_elements );
              if ( actions not_eq nullptr )
                for ( auto index_of_element = 0; index_of_element < number_of_elements; ++index_of_element )
                  joystick_state_analog( index_of_joystick, index_of_element, actions[index_of_element] );
            }
            // name
            joystick_state_name( index_of_joystick, glfwGetJoystickName( index_of_joystick ) );
          }
#endif
        }
        
      public:
        
        ~GLFW3_t() override
        { 
          while( not _dtor_hooks.empty() )
          { 
            _dtor_hooks.front()();
            _dtor_hooks.pop_front();
          }
        }
        
        auto get_glfw3_window_handle() const -> const decltype(_window)
        {
          return _window;
        }
        
        auto default_initialize_params_create_window(initialize_params_t& ps) const
          -> void
        {
          // http://www.glfw.org/docs/latest/group__window.html#ga5c336fddf2cbb5b92f65f10fb6043344
          ps.put( "width"  , 320 );
          ps.put( "height" , 240 );
          ps.put( "title"  , "some other wonderland with GLFW3" );
          ps.put<GLFWmonitor*>( "GLFW.monitor", nullptr );
          ps.put<GLFWwindow* >( "GLFW.window" , nullptr );
        }
        
        auto default_initialize_params_window_hints(initialize_params_t& ps) const
          -> void
        {
          // http://www.glfw.org/docs/latest/window.html#window_hints_values
          ps.put( "resizable"        , true );
          ps.put( "visible"          , true );
          ps.put( "decorated"        , true );
          ps.put( "red_bits"         , 8 );
          ps.put( "green_bits"       , 8 );
          ps.put( "blue_bits"        , 8 );
          ps.put( "alpha_bits"       , 8 );
          ps.put( "depth_bits"       , 24 );
          ps.put( "stencil_bits"     , 8 );
          ps.put( "accum_red_bits"   , 0 );
          ps.put( "accum_green_bits" , 0 );
          ps.put( "accum_blue_bits"  , 0 );
          ps.put( "accum_alpha_bits" , 0 );
          ps.put( "aux_buffers"  , 0 );
          ps.put( "samples"      , 0 );
          ps.put( "refresh_rate" , 0 );
          ps.put( "stereo"       , false );
          ps.put( "srgb_capable" , false );
          ps.put( "client_api"   , initialize_params::client_api::opengl );
          ps.put( "context_version_major" , 1 );
          ps.put( "context_version_minor" , 0 );
          ps.put( "context_robustness"    , initialize_params::context_robustness::no_robustness );
          ps.put( "opengl_forward_compat" , false );
          ps.put( "opengl_debug_context"  , false );
          ps.put( "opengl_profile" , initialize_params::opengl_profile::any );
        }
        
        auto default_initialize_params_window_position(initialize_params_t& ps) const
          -> void
        {
          // http://www.glfw.org/docs/latest/group__window.html#ga1abb6d690e8c88e0c8cd1751356dbca8
          ps.put( "x" , 0 );
          ps.put( "y" , 0 );
        }
        
        auto default_initialize_params() const
          -> initialize_params_t override
        {
          initialize_params_t ps;
          default_initialize_params_window_position(ps);
          default_initialize_params_window_hints(ps);
          default_initialize_params_create_window(ps);
          return ps;
        }
        
        auto initialize( initialize_params_t&& ps )
          -> void override
        {
          initialize_glfw();
          initialize_set_error_callback();
          initialize_window_hints(ps);
          initialize_create_window(ps);
          window_position(ps);
          initialize_make_contex_current();
          initialize_set_scroll_callback();
          initialize_set_frame_buffer_size_callback();
        }
        
        auto after_render()
          -> void override
        {
          glfwSwapBuffers( _window );
          glfwPollEvents();
          process_input_states();
        }
        
        auto to_continue() const
          -> bool override
        { return not glfwWindowShouldClose( _window ); }
        
        auto to_continue(const bool b)
          -> void override
        { glfwSetWindowShouldClose( _window, int( not b ) ); }
        
        auto version() const
          -> version_t override
        { return { GLFW_VERSION_MAJOR , GLFW_VERSION_MINOR , GLFW_VERSION_REVISION }; }
        
        auto name() const
          -> std::string override
        { return "GLFW3"; }
        
        auto title( const std::string& value ) const
          -> void
        { glfwSetWindowTitle( _window, value.data() ); }
        
      };
      
#ifndef WRP_WONDERLAND_SUBSYSTEM_T
#define WRP_WONDERLAND_SUBSYSTEM_T
      using subsystem_t = GLFW3_t;
#endif
      
    }
  }
}
