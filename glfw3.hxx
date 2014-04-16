#pragma once

#include <forward_list>
#include <unordered_map>
#include <limits>

#include <GLFW/glfw3.h>

#include "subsystem_base.hxx"

namespace
{
  using window_owner_dictionary_t = std::unordered_map
    < GLFWwindow*
    , std::weak_ptr<wonder_rabbit_project::wonderland::subsystem::subsystem_base_t>
    >;
    
  window_owner_dictionary_t window_owner_dictionary;
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
          
          glfwWindowHint( GLFW_RESIZABLE , get("resizable") );
          glfwWindowHint( GLFW_VISIBLE   , get("visible" ) );
          glfwWindowHint( GLFW_DECORATED , get("decorated" ) );
          glfwWindowHint( GLFW_RED_BITS , get("red_bits" ) );
          glfwWindowHint( GLFW_GREEN_BITS , get("green_bits" ) );
          glfwWindowHint( GLFW_BLUE_BITS , get("blue_bits" ) );
          glfwWindowHint( GLFW_ALPHA_BITS , get("alpha_bits" ) );
          glfwWindowHint( GLFW_DEPTH_BITS , get("depth_bits" ) );
          glfwWindowHint( GLFW_STENCIL_BITS , get("stencil_bits" ) );
          glfwWindowHint( GLFW_ACCUM_RED_BITS , get("accum_red_bits" ) );
          glfwWindowHint( GLFW_ACCUM_GREEN_BITS , get("accum_green_bits" ) );
          glfwWindowHint( GLFW_ACCUM_BLUE_BITS , get("accum_blue_bits" ) );
          glfwWindowHint( GLFW_ACCUM_ALPHA_BITS , get("accum_alpha_bits" ) );
          glfwWindowHint( GLFW_AUX_BUFFERS , get("aux_buffers" ) );
          glfwWindowHint( GLFW_SAMPLES , get("samples" ) );
          glfwWindowHint( GLFW_REFRESH_RATE , get("refresh_rate" ) );
          glfwWindowHint( GLFW_STEREO , get("stereo" ) );
          glfwWindowHint( GLFW_SRGB_CAPABLE , get("srgb_capable" ) );
          glfwWindowHint( GLFW_CLIENT_API , get("client_api" ) );
          glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR , get("context_version_major" ) );
          glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR , get("context_version_minor" ) );
          glfwWindowHint( GLFW_CONTEXT_ROBUSTNESS , get("context_robustness" ) );
          glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT , get("opengl_forward_compat" ) );
          glfwWindowHint( GLFW_OPENGL_DEBUG_CONTEXT , get("opengl_debug_context" ) );
          glfwWindowHint( GLFW_OPENGL_PROFILE , get("opengl_profile" ) );
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
          
          ::window_owner_dictionary.emplace( window, shared_from_this() );
          
          _dtor_hooks.emplace_front( [ window ]
          {
            ::window_owner_dictionary.erase( window );
            glfwDestroyWindow( window );
          });
        }
        
        auto initialize_make_contex_current() const ->void
        { glfwMakeContextCurrent( _window ); }
        
        auto initialize_set_keyboard_callback() const -> void
        {
          glfwSetKeyCallback
          ( _window
          , [] ( GLFWwindow* window, int key, int scancode, int action, int mods )
            {
              auto this_ = ::window_owner_dictionary.at(window).lock();
              
              // TODO: to use scancode with libWRP-key
              key_code_t fixed_key = key::reserved;
              
              // 1 - 9
              if ( key >= 49 and key <= 57 )
                fixed_key = key::keyboard_1_and_exclamation + key - 49;
              // A - Z
              else if ( key >= 65 and key <= 90 )
                fixed_key = key::keyboard_a_and_A + key - 65;
              // F1 - F12
              else if ( key >= 290 and key <= 301 )
                fixed_key = key::keyboard_f1 + key - 290;
              // F13 - F24
              else if ( key >= 302 and key <= 313 )
                fixed_key = key::keyboard_f13 + key - 302;
              // Num1 - Num9
              else if ( key >= 321 and key <= 329 )
                fixed_key = key::keypad_1_and_end + key - 321;
              // Num{ / * - + ENTER }
              else if ( key >= 331 and key <= 335 )
                fixed_key = key::keypad_slash + key - 331;
              // modifiers ( L{S,C,A,S} R{S,C,A,S} )
              else if ( key >= 340 and key <= 347 )
                fixed_key = key::keyboard_left_shift + key - 340;
              else
                switch (key)
                { case 32: fixed_key = key::keyboard_spacebar; break;
                  case 39: fixed_key = key::keyboard_single_quotation_and_double_quotation; break;
                  case 44: fixed_key = key::keyboard_comma_and_angle_bracket_open; break;
                  case 45: fixed_key = key::keyboard_minus_and_underscore; break;
                  case 46: fixed_key = key::keyboard_dot_and_angle_bracket_close; break;
                  case 47: fixed_key = key::keyboard_slash_and_question; break;
                  case 48: fixed_key = key::keyboard_0_and_round_bracket_end; break;
                  case 91: fixed_key = key::keyboard_box_bracket_open_and_curly_bracket_open; break;
                  case 92: fixed_key = key::keyboard_back_slash_and_vertical_bar; break;
                  case 93: fixed_key = key::keyboard_box_bracket_close_and_curly_bracket_close; break;
                  case 96: fixed_key = key::keyboard_grave_accent_and_tilde; break;
                  case 161: fixed_key = key::keyboard_non_us_number_mark_and_tilde; break;
                  case 162: fixed_key = key::keyboard_non_us_backslash_and_vertical_bar; break;
                  case 256: fixed_key = key::keyboard_escape; break;
                  case 257: fixed_key = key::keyboard_return_enter; break;
                  case 258: fixed_key = key::keyboard_tab; break;
                  case 259: fixed_key = key::keyboard_delete_backspace; break;
                  case 260: fixed_key = key::keyboard_insert; break;
                  case 261: fixed_key = key::keyboard_delete_forward; break;
                  case 262: fixed_key = key::keyboard_right_arrow; break;
                  case 263: fixed_key = key::keyboard_left_arrow; break;
                  case 264: fixed_key = key::keyboard_down_arrow; break;
                  case 265: fixed_key = key::keyboard_up_arrow; break;
                  case 266: fixed_key = key::keyboard_page_up; break;
                  case 267: fixed_key = key::keyboard_page_down; break;
                  case 268: fixed_key = key::keyboard_home; break;
                  case 269: fixed_key = key::keyboard_end; break;
                  case 280: fixed_key = key::keyboard_caps_lock; break;
                  case 281: fixed_key = key::keyboard_scroll_lock; break;
                  case 282: fixed_key = key::keypad_num_lock_and_clear; break;
                  case 283: fixed_key = key::keyboard_print_screen; break;
                  case 284: fixed_key = key::keyboard_pause; break;
                  case 320: fixed_key = key::keypad_0_and_insert; break;
                  case 336: fixed_key = key::keypad_equal; break;
                  case 348: fixed_key = key::keyboard_menu; break;
                };
              
              if ( fixed_key )
                this_ -> keyboard_state( fixed_key, bool(action) );
              
              /*
              const auto mods_fire = [ mods , &this_ ](int key, key_code_t left, key_code_t right)
              {
                const auto fire = bool( mods & key );
                this_ -> keyboard_state( left , fire );
                this_ -> keyboard_state( right, fire );
              };
              
              mods_fire( GLFW_MOD_SHIFT  , key::keyboard_left_shift  , key::keyboard_right_shift   );
              mods_fire( GLFW_MOD_CONTROL, key::keyboard_left_control, key::keyboard_right_control );
              mods_fire( GLFW_MOD_ALT    , key::keyboard_left_alt    , key::keyboard_right_alt     );
              mods_fire( GLFW_MOD_SUPER  , key::keyboard_left_gui    , key::keyboard_right_gui     );
              */
            }
          );
        }
        
        auto initialize_set_frame_buffer_size_callback() const -> void
        {
          glfwSetFramebufferSizeCallback
          ( _window
          , [](GLFWwindow* window, int width, int height)
            { glViewport(0, 0, width, height); }
          );
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
          ps.put( "resizable" , GL_TRUE );
          ps.put( "visible" , GL_TRUE );
          ps.put( "decorated" , GL_TRUE );
          ps.put( "red_bits" , 8 );
          ps.put( "green_bits" , 8 );
          ps.put( "blue_bits" , 8 );
          ps.put( "alpha_bits" , 8 );
          ps.put( "depth_bits" , 24 );
          ps.put( "stencil_bits" , 8 );
          ps.put( "accum_red_bits" , 0 );
          ps.put( "accum_green_bits" , 0 );
          ps.put( "accum_blue_bits" , 0 );
          ps.put( "accum_alpha_bits" , 0 );
          ps.put( "aux_buffers" , 0 );
          ps.put( "samples" , 0 );
          ps.put( "refresh_rate" , 0 );
          ps.put( "stereo" , GL_FALSE );
          ps.put( "srgb_capable" , GL_FALSE );
          ps.put( "client_api" , GLFW_OPENGL_API );
          ps.put( "context_version_major" , 1 );
          ps.put( "context_version_minor" , 0 );
          ps.put( "context_robustness" , GLFW_NO_ROBUSTNESS );
          ps.put( "opengl_forward_compat" , GL_FALSE );
          ps.put( "opengl_debug_context" , GL_FALSE );
          ps.put( "opengl_profile" , GLFW_OPENGL_ANY_PROFILE );
        }
        
        auto default_initialize_params() const
          -> initialize_params_t override
        {
          initialize_params_t ps;
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
          initialize_make_contex_current();
          initialize_set_keyboard_callback();
          initialize_set_frame_buffer_size_callback();
        }
        
        auto after_render()
          -> void override
        {
          glfwSwapBuffers( _window );
          glfwPollEvents();
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
        
      };
        
#ifndef WRP_WONDERLAND_SUBSYSTEM_T
#define WRP_WONDERLAND_SUBSYSTEM_T
      using subsystem_t = GLFW3_t;
#endif
      
    }
  }
}