#pragma once

#include <forward_list>

#include <sprout/math/sqrt.hpp>

#include <SDL/SDL.h>

#include "subsystem_base.hxx"

namespace wonder_rabbit_project
{
  namespace wonderland
  {
    namespace subsystem
    {
      
      struct sdl1_runtime_error_t
        : subsystem_runtime_error_t
      {
        sdl1_runtime_error_t(const std::string& what)
          : subsystem_runtime_error_t(what)
        { }
      };
      
      class SDL1_t
        : public subsystem_base_t
      {
        using dtor_hook_t  = std::function<void()>;
        using dtor_hooks_t = std::forward_list<dtor_hook_t>;
        
        dtor_hooks_t _dtor_hooks;
        
        SDL_Surface*  _surface;
        
        auto initialize_sdl(initialize_params_t& ps) -> void
        {
          initialize_params_t dps;
          default_initialize_params_sdl_init(dps);
          
          const auto get = [ &ps, &dps ](const char* key)
            { return ps.get(key, dps.get<bool>(key) ); };
            
          std::uint32_t flag = 0x00000000;
          
          const auto set_flag = [ &get, &flag ](const char* key, std::uint32_t plus_flag)
            { if ( get(key) ) flag |= plus_flag; };
          
          set_flag( "SDL.init_timer", SDL_INIT_TIMER );
          set_flag( "SDL.init_audio", SDL_INIT_AUDIO );
          set_flag( "SDL.init_video", SDL_INIT_VIDEO );
#ifndef EMSCRIPTEN
          set_flag( "SDL.init_cdrom", SDL_INIT_CDROM );
#endif
#ifndef EMSCRIPTEN
          set_flag( "SDL.init_joystick", SDL_INIT_JOYSTICK );
#endif
          set_flag( "SDL.init_everything" , SDL_INIT_EVERYTHING );
          set_flag( "SDL.init_noparachute", SDL_INIT_NOPARACHUTE );
          
          const auto r = SDL_Init( flag );
          if ( r == -1 )
            throw sdl1_runtime_error_t( std::string("SDL_Init failed. return value: -1" ) );
          
          _dtor_hooks.emplace_front( []{ SDL_Quit(); } );
        }
        
        auto initialize_create_window(initialize_params_t& ps) -> void
        {
          initialize_params_t dps;
          default_initialize_params_create_window(dps);
          
          // TODO: to template if supported C++14
          const auto get_bool = [ &ps, &dps ](const char* key){ return ps.get(key, dps.get<bool>(key) ); };
          const auto get_int  = [ &ps, &dps ](const char* key){ return ps.get(key, dps.get<int>(key) ); };
          
          std::uint32_t flag = 0x00000000;
          
          if ( get_bool("resizable") )
            flag |= SDL_RESIZABLE;
          if ( not get_bool("decorated") )
            flag |= SDL_NOFRAME;
          if ( get_bool("SDL.fullscreen") )
            flag |= SDL_FULLSCREEN;
          if ( get_bool( "SDL.anyformat" ) )
            flag |= SDL_ANYFORMAT;
          if ( get_bool( "SDL.hwsurface" ) )
            flag |= SDL_HWSURFACE;
          if ( get_bool( "SDL.asyncblit" ) )
            flag |= SDL_ASYNCBLIT;
          if ( get_bool( "SDL.hwpalette" ) )
            flag |= SDL_HWPALETTE;
          if ( get_bool( "SDL.fullscreen" ) )
            flag |= SDL_FULLSCREEN;
          if ( get_bool( "SDL.doublebuf" ) )
            flag |= SDL_DOUBLEBUF;
          
          const int bpp = get_int("red_bits")
                        + get_int("green_bits")
                        + get_int("blue_bits")
                        + get_int("alpha_bits")
                        ;
          
          const auto surface = _surface
            = SDL_SetVideoMode
              ( get_int("width" )
              , get_int("height")
              , bpp
              , flag
              );
              
          if ( not surface )
            throw sdl1_runtime_error_t
            ( "SDL_CreateWindow failed. window is nullptr." );
          
          /*
          if ( flag & SDL_WINDOW_OPENGL )
          {
            const auto sdl_gl_context = SDL_GL_CreateContext( window );
            //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
            //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
            //SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            
            _dtor_hooks.emplace_front( [ sdl_gl_context ]
            {
              SDL_GL_DeleteContext( sdl_gl_context );
            });
          }
          */
        }
        
        auto initialize_set_caption(initialize_params_t ps)
          -> void const
        {
          initialize_params_t dps;
          default_initialize_params_set_caption(dps);
          
          SDL_WM_SetCaption( ps.get("title" ,dps.get<std::string>("title")).data(), nullptr );
        }
        
        auto initialize_joystick() -> void
        {
#ifndef EMSCRIPTEN
          const auto number_of_joysticks = SDL_NumJoysticks();
          
          for ( auto index_of_joystick = 0; index_of_joystick < number_of_joysticks; ++index_of_joystick )
          {
            const auto joystick = SDL_JoystickOpen( index_of_joystick );
            
  #if SDL_VERSION_ATLEAST(1,3,0)
            joystick_state_name( index_of_joystick, SDL_JoystickNameForIndex( index_of_joystick ) );
  #else
            joystick_state_name( index_of_joystick, SDL_JoystickName( index_of_joystick ) );
  #endif
            if ( auto n = SDL_JoystickNumButtons( joystick ) )
              joystick_state_digital( index_of_joystick, n - 1, false );
            if ( auto n = SDL_JoystickNumAxes   ( joystick ) )
              joystick_state_analog ( index_of_joystick, n - 1, 0.    );
            if ( auto n = SDL_JoystickNumBalls  ( joystick ) )
              joystick_state_ball   ( index_of_joystick, n - 1, {}    );
            if ( auto n = SDL_JoystickNumHats   ( joystick ) )
              joystick_state_hat    ( index_of_joystick, n - 1, {}    );
            
            _dtor_hooks.emplace_front( [ joystick ]
            {
  #if SDL_VERSION_ATLEAST(1,3,0)
              if ( SDL_JoystickGetAttached( joystick ) )
  #endif
                SDL_JoystickClose( joystick );
            });
          }
#endif
        }
        
        auto process_events() -> void
        {
          SDL_Event e;
          
          bool has_key_event = false;
          
          while ( SDL_PollEvent(&e) )
            switch( e.type )
            { case SDL_KEYDOWN:
              case SDL_KEYUP:
                has_key_event = true;
                break;
              case SDL_MOUSEMOTION:
                pointing_states_position( { e.motion.x, e.motion.y } );
                break;
              case SDL_MOUSEBUTTONDOWN:
              case SDL_MOUSEBUTTONUP:
              {
                auto action = e.button.state == SDL_PRESSED;
                switch ( e.button.button )
                {
                  case SDL_BUTTON_LEFT:
                    pointing_states_button<0>(action);
                    break;
                  case SDL_BUTTON_RIGHT:
                    pointing_states_button<1>(action);
                    break;
                  case SDL_BUTTON_MIDDLE:
                    pointing_states_button<2>(action);
                    break;
                }
                break;
              }
#ifndef EMSCRIPTEN
              case SDL_JOYAXISMOTION:
                joystick_state_analog
                ( e.jaxis.which
                , e.jaxis.axis
                , (double(e.jaxis.value) + .5) / 32767.5
                );
                break;
              case SDL_JOYBALLMOTION:
                joystick_state_ball
                ( e.jball.which
                , e.jball.ball
                , { e.jball.xrel, e.jball.yrel }
                );
                break;
              case SDL_JOYHATMOTION:
              {
                glm::vec2 hat;
                
                constexpr auto sqrt2div2 = sprout::math::sqrt(2.) / 2.;
                
                switch( e.jhat.value )
                { case SDL_HAT_CENTERED:
                    break;
                  case SDL_HAT_UP:
                    hat.y = 1;
                    break;
                  case SDL_HAT_RIGHT:
                    hat.x = 1;
                    break;
                  case SDL_HAT_DOWN:
                    hat.y = -1;
                    break;
                  case SDL_HAT_LEFT:
                    hat.x = -1;
                    break;
                  case SDL_HAT_RIGHTUP:
                    hat = { sqrt2div2 , sqrt2div2 };
                    break;
                  case SDL_HAT_RIGHTDOWN:
                    hat = { sqrt2div2 , -sqrt2div2 };
                    break;
                  case SDL_HAT_LEFTUP:
                    hat = { -sqrt2div2, sqrt2div2 };
                    break;
                  case SDL_HAT_LEFTDOWN:
                    hat = { -sqrt2div2, -sqrt2div2 };
                    break;
                }
                
                joystick_state_hat
                ( e.jhat.which
                , e.jhat.hat
                , std::move(hat)
                );
                
                break;
              }
              case SDL_JOYBUTTONDOWN:
              case SDL_JOYBUTTONUP:
                joystick_state_digital
                ( e.jbutton.which
                , e.jbutton.button
                , e.jbutton.state == SDL_PRESSED
                );
                break;
  #if SDL_VERSION_ATLEAST(1,3,0)
              case SDL_JOYDEVICEADDED:
              case SDL_JOYDEVICEREMOVED:
                break;
  #endif
#endif
            }
          
          if ( has_key_event )
            process_events_keyevent();
        }
        
        auto process_events_keyevent() -> void
        {
          using sdl_key_states_t = const std::uint8_t*;
#if SDL_VERSION_ATLEAST(1,3,0)
          sdl_key_states_t sdl_key_states = SDL_GetKeyboardState(nullptr);
#else
          sdl_key_states_t sdl_key_states = SDL_GetKeyState(nullptr);
#endif
#if SDL_VERSION_ATLEAST(1,3,0)
          for ( int n = SDLK_UNKNOWN; n < SDLK_LAST; ++n)
#else
          for ( int n = SDLK_FIRST; n < SDLK_LAST; ++n)
#endif
            keyboard_state( key_code_from_sdl1(n), bool(sdl_key_states[n]) );
        }
        
      public:
        
        ~SDL1_t() override
        { 
          while( not _dtor_hooks.empty() )
          { 
            _dtor_hooks.front()();
            _dtor_hooks.pop_front();
          }
        }
        
        auto default_initialize_params_sdl_init(initialize_params_t& ps) const
          -> void
        {
          ps.put( "SDL.init_timer"          , false );
          ps.put( "SDL.init_audio"          , false );
          ps.put( "SDL.init_video"          , true  );
          ps.put( "SDL.init_cdrom"          , false );
          ps.put( "SDL.init_joystick"       , true  );
          ps.put( "SDL.init_everything"     , false );
          ps.put( "SDL.init_noparachute"    , false );
        }
        
        auto default_initialize_params_create_window(initialize_params_t& ps) const
          -> void
        {
          // TODO: support; SDL_SetWindowPosition:471
          //ps.put( "x"      ,   0 );
          //ps.put( "y"      ,   0 );
          
          ps.put( "width"  , 320 );
          ps.put( "height" , 240 );
          
          // convert to bpp as int param of SDL_SetVideoMode
          ps.put( "red_bits"         , 8 );
          ps.put( "green_bits"       , 8 );
          ps.put( "blue_bits"        , 8 );
          ps.put( "alpha_bits"       , 8 );
          
          // convert to SDL_RESIZABLE
          ps.put( "resizable" , true );
          // convert to SDL_NOFRAME
          ps.put( "decorated" , true );
          
          // SDL
          ps.put( "SDL.anyformat"  , false );
          ps.put( "SDL.hwsurface"  , true );
          ps.put( "SDL.asyncblit"  , true );
          ps.put( "SDL.hwpalette"  , false );
          ps.put( "SDL.fullscreen" , false );
          ps.put( "SDL.doublebuf"  , true );
        }
        
        auto default_initialize_params_set_caption(initialize_params_t& ps) const
          -> void
        {
          ps.put( "title"  , "some other wonderland with SDL1" );
        }
        
        auto default_initialize_params() const
          -> initialize_params_t override
        {
          initialize_params_t ps;
          default_initialize_params_set_caption(ps);
          default_initialize_params_create_window(ps);
          default_initialize_params_sdl_init(ps);
          return ps;
        }
        
        auto initialize( initialize_params_t&& ps )
          -> void override
        {
          initialize_sdl(ps);
          initialize_create_window(ps);
          initialize_joystick();
        }
        
        auto after_render()
          -> void override
        {
          SDL_UpdateRect( _surface, 0, 0, 0, 0 );
          SDL_GL_SwapBuffers( );
          process_events();
        }
        
        auto version() const
          -> version_t override
        { return { SDL_MAJOR_VERSION , SDL_MINOR_VERSION , SDL_PATCHLEVEL }; }
        
        auto name() const
          -> std::string override
        { return "SDL1"; }
        
      };
        
#ifndef WRP_WONDERLAND_SUBSYSTEM_T
#define WRP_WONDERLAND_SUBSYSTEM_T
      using subsystem_t = SDL1_t;
#endif
      
    }
  }
}