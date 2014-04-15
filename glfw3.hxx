#pragma once

#include <forward_list>
#include <unordered_map>

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
          default_initialize_params_create_window(dps);
          
          const auto get = [&ps, &dps](const char* name)
          { return ps.get("resizable", dps.get<int>("resizable")); };
          
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
              ::window_owner_dictionary
                .at(window)
                  .lock()
                    -> keyboard_state(unsigned(key), bool(action));
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
        
        ~GLFW3_t()
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
          default_initialize_params_create_window(ps);
          default_initialize_params_window_hints(ps);
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