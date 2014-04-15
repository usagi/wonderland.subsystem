#pragma once

#include <forward_list>
#include <unordered_map>

#include <GL/glfw.h>

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
        
      public:
        static constexpr const char* initialize_param_key_width   = "width";
        static constexpr const char* initialize_param_key_height  = "height";
        static constexpr const char* initialize_param_key_title   = "title";
        static constexpr const char* initialize_param_key_monitor = "monitor";
        static constexpr const char* initialize_param_key_window  = "window";
        
        static constexpr int initialize_param_default_width  = 320;
        static constexpr int initialize_param_default_height = 240;
        static constexpr const char* initialize_param_default_title = "some other wonderland with GLFW3";
        static constexpr GLFWmonitor* initialize_param_default_monitor = nullptr;
        static constexpr GLFWwindow*  initialize_param_default_window  = nullptr;
        
        ~GLFW3_t()
        { 
          while( not _dtor_hooks.empty() )
          { 
            _dtor_hooks.front()();
            _dtor_hooks.pop_front();
          }
        }
        
        auto default_initialize_params() const
          -> initialize_params_t
        {
          return
          { { initialize_param_key_width  , initialize_param_default_width   }
          , { initialize_param_key_height , initialize_param_default_height  }
          , { initialize_param_key_title  , initialize_param_default_title   }
          , { initialize_param_key_monitor, initialize_param_default_monitor }
          , { initialize_param_key_window , initialize_param_default_window  }
          };
        }
        
        auto initialize( initialize_params_t&& ps )
          -> void override
        {
          ps = fill_initialize_params( std::move(ps) );
          
          {
            const auto r = glfwInit();
            if ( not r )
              throw glfw3_runtime_error_t( std::string("glfwInit failed. return value: ") + std::to_string(r) );
          }
          
          _dtor_hooks.emplace_front( []{ glfwTerminate(); } );
          
          glfwSetErrorCallback
          ( [](int error, const char* description)
            { throw glfw3_runtime_error_t
              ( std::string("glfw error: error = ") + std::to_string(error) 
              + std::string(" , description = ") + std::string(description)
              );
            }
          );
          
          const auto window
            = glfwCreateWindow
              ( boost::any_cast< int          >( ps[initialize_param_key_width  ] )
              , boost::any_cast< int          >( ps[initialize_param_key_height ] )
              , boost::any_cast< const char*  >( ps[initialize_param_key_title  ] )
              , boost::any_cast< GLFWmonitor* >( ps[initialize_param_key_monitor] )
              , boost::any_cast< GLFWwindow*  >( ps[initialize_param_key_window ] )
              );
          
          if ( not window )
            throw glfw3_runtime_error_t
            ( "glfwCreateWindow failed. window is nullptr." );
          
          ::window_owner_dictionary.emplace( window, shared_from_this() );
          
          _dtor_hooks.emplace_front( [&window]
          {
            ::window_owner_dictionary.erase( window );
            glfwDestroyWindow( window );
          });
          
          
          glfwMakeContextCurrent( window );
          
          glfwSetKeyCallback
          ( window
          , [] ( GLFWwindow* window, int key, int scancode, int action, int mods )
            {
              ::window_owner_dictionary
                .at(window)
                  .lock()
                    -> keyboard_state(unsigned(key), bool(action));
            }
          );
          
          glfwSetFramebufferSizeCallback
          ( window
          , [](GLFWwindow* window, int width, int height)
            { glViewport(0, 0, width, height); }
          );
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
        { glfwSetWindowShouldClose( _window, int(b) ); }
        
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