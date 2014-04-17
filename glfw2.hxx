#pragma once

#include <forward_list>
#include <unordered_map>

#include <GL/glfw.h>

#include "subsystem_base.hxx"

namespace
{
  using subsystems_t
    = std::forward_list
      < std::weak_ptr
        < wonder_rabbit_project::wonderland::subsystem::subsystem_base_t
        >
      >;
  
  subsystems_t subsystems;
}

namespace wonder_rabbit_project
{
  namespace wonderland
  {
    namespace subsystem
    {
      
      struct glfw2_runtime_error_t
        : subsystem_runtime_error_t
      {
        glfw2_runtime_error_t(const std::string& what)
          : subsystem_runtime_error_t(what)
        { }
      };
      
      class GLFW2_t
        : public subsystem_base_t
      {
        using dtor_hook_t  = std::function<void()>;
        using dtor_hooks_t = std::forward_list<dtor_hook_t>;
        
        dtor_hooks_t _dtor_hooks;
        
        auto initialize_glfw() -> void
        {
          const auto r = glfwInit();
          if ( not r )
            throw glfw2_runtime_error_t( std::string("glfwInit failed. return value: ") + std::to_string(r) );
          
          _dtor_hooks.emplace_front( []{ glfwTerminate(); } );
        }
        
        auto initialize_window_hints(initialize_params_t& ps) -> void
        {
          initialize_params_t dps;
          default_initialize_params_window_hints(dps);
          
          const auto get = [&ps, &dps](const char* name)
          { return ps.get(name, dps.get<int>(name)); };
          
          glfwOpenWindowHint( GLFW_REFRESH_RATE , get("refresh_rate" ) );
          glfwOpenWindowHint( GLFW_ACCUM_RED_BITS , get("accum_red_bits" ) );
          glfwOpenWindowHint( GLFW_ACCUM_GREEN_BITS , get("accum_green_bits" ) );
          glfwOpenWindowHint( GLFW_ACCUM_BLUE_BITS , get("accum_blue_bits" ) );
          glfwOpenWindowHint( GLFW_ACCUM_ALPHA_BITS , get("accum_alpha_bits" ) );
          glfwOpenWindowHint( GLFW_AUX_BUFFERS , get("aux_buffers" ) );
          glfwOpenWindowHint( GLFW_STEREO , get("stereo" ) );
          
          // GLFW3 convertiblity, but GLFW2 name is GLFW_WINDOW_NO_RESIZE and value is reversed.
          glfwOpenWindowHint( GLFW_WINDOW_NO_RESIZE , not get("resizable") );
          
          // GLFW3 convertiblity, but GLFW2 name is GLFW_FSAA_SAMPLES.
          glfwOpenWindowHint( GLFW_FSAA_SAMPLES , get("samples" ) );
          
          // GLFW3 convertiblity, but GLFW2 name is GLFW_OPENGL_VERSION_MAJOR
          glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR , get("context_version_major" ) );
          // GLFW3 convertiblity, but GLFW2 name is GLFW_OPENGL_VERSION_MINOR and default value is 1(GLLFW3 is 0).
          glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR , get("context_version_minor" ) );
          
          glfwOpenWindowHint( GLFW_OPENGL_FORWARD_COMPAT , get("opengl_forward_compat" ) );
          glfwOpenWindowHint( GLFW_OPENGL_DEBUG_CONTEXT , get("opengl_debug_context" ) );
          // GLFW3 convertiblity, but GLFW2 default value is 0(GLFW3 defined GLFW_OPENGL_ANY_PROFILE to 0).
          glfwOpenWindowHint( GLFW_OPENGL_PROFILE , get("opengl_profile" ) );
        }
        
        auto initialize_open_window(initialize_params_t& ps) -> void
        {
          initialize_params_t dps;
          default_initialize_params_create_window(dps);
          
          const auto get = [ &ps, &dps ](const char* name)
          { return ps.get(name, dps.get<int>(name)); };
          
          const auto result
            = glfwOpenWindow
              ( get("width")
              , get("height")
              , get("red_bits")
              , get("green_bits")
              , get("blue_bits")
              , get("alpha_bits")
              , get("depth_bits")
              , get("stencil_bits")
              , get("mode")
              );
              
          if ( not result )
            throw glfw2_runtime_error_t
            ( "glfwOpenWindow failed. window is nullptr." );
          
          ::subsystems.emplace_front( shared_from_this() );
          
          _dtor_hooks.emplace_front( [ this ]
          {
            //::subsystems.remove( std::move( std::weak_ptr<subsystem_t>( this->shared_from_this() ) ) );
            glfwCloseWindow();
          });
        }
        
        auto initialize_set_window_title(initialize_params_t& ps) const -> void
        {
          initialize_params_t dps;
          default_initialize_params_window_title(dps);
          
          glfwSetWindowTitle( ps.get("title", dps.get<std::string>("title")).data() );
        }
        
        auto initialize_set_keyboard_callback() const -> void
        {
          glfwSetKeyCallback
          ( [] ( int key, int action )
            {
              auto this_ = ::subsystems.front().lock();
              
              const auto fixed_key = key_code_from_glfw(key);
              if ( fixed_key )
                this_ -> keyboard_state( fixed_key, bool(action) );
            }
          );
        }
        
      public:
        
        ~GLFW2_t() override
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
          ps.put( "width"  , 320 );
          ps.put( "height" , 240 );
          ps.put( "red_bits" , 8 );
          ps.put( "green_bits" , 8 );
          ps.put( "blue_bits" , 8 );
          ps.put( "alpha_bits" , 8 );
          ps.put( "depth_bits" , 24 );
          ps.put( "stencil_bits" , 8 );
          ps.put( "mode" , GLFW_WINDOW );
        }
        
        auto default_initialize_params_window_hints(initialize_params_t& ps) const
          -> void
        {
          ps.put( "refresh_rate" , 0 );
          ps.put( "accum_red_bits" , 0 );
          ps.put( "accum_green_bits" , 0 );
          ps.put( "accum_blue_bits" , 0 );
          ps.put( "accum_alpha_bits" , 0 );
          ps.put( "aux_buffers" , 0 );
          ps.put( "stereo" , GL_FALSE );
          
          // GLFW3 convertiblity, but GLFW2 name is GLFW_WINDOW_NO_RESIZE and value is reversed.
          ps.put( "resizable" , GL_TRUE );
          
          // GLFW3 convertiblity, but GLFW2 name is GLFW_FSAA_SAMPLES.
          ps.put( "samples" , 0 );
          
          // GLFW3 convertiblity, but GLFW2 name is GLFW_OPENGL_VERSION_MAJOR
          ps.put( "context_version_major" , 1 );
          // GLFW3 convertiblity, but GLFW2 name is GLFW_OPENGL_VERSION_MINOR and default value is 1(GLLFW3 is 0).
          ps.put( "context_version_minor" , 1 );
          
          ps.put( "opengl_forward_compat" , GL_FALSE );
          ps.put( "opengl_debug_context" , GL_FALSE );
          // GLFW3 convertiblity, but GLFW2 default value is 0(GLFW3 defined GLFW_OPENGL_ANY_PROFILE to 0).
          ps.put( "opengl_profile" , 0 );
        }
        
        auto default_initialize_params_window_title(initialize_params_t& ps) const
          -> void
        { ps.put( "title" , "some other wonderland with GLFW2" ); }
        
        auto default_initialize_params() const
          -> initialize_params_t override
        {
          initialize_params_t ps;
          default_initialize_params_window_title(ps);
          default_initialize_params_window_hints(ps);
          default_initialize_params_create_window(ps);
          return ps;
        }
        
        auto initialize( initialize_params_t&& ps )
          -> void override
        {
          initialize_glfw();
          initialize_window_hints(ps);
          initialize_open_window(ps);
          initialize_set_window_title(ps);
          initialize_set_keyboard_callback();
        }
        
        auto after_render()
          -> void override
        {
          glfwSwapBuffers();
          glfwPollEvents();
        }
        
        auto version() const
          -> version_t override
        { return { GLFW_VERSION_MAJOR , GLFW_VERSION_MINOR , GLFW_VERSION_REVISION }; }
        
        auto name() const
          -> std::string override
        { return "GLFW2"; }
        
      };
        
#ifndef WRP_WONDERLAND_SUBSYSTEM_T
#define WRP_WONDERLAND_SUBSYSTEM_T
      using subsystem_t = GLFW2_t;
#endif
      
    }
  }
}