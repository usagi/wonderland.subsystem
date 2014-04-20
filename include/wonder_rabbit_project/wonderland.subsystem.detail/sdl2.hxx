#pragma once

#include <forward_list>

#include <sprout/math/sqrt.hpp>

#include <SDL2/SDL.h>

#include "subsystem_base.hxx"

namespace wonder_rabbit_project
{
  namespace wonderland
  {
    namespace subsystem
    {
      
      struct sdl2_runtime_error_t
        : subsystem_runtime_error_t
      {
        sdl2_runtime_error_t(const std::string& what)
          : subsystem_runtime_error_t(what)
        { }
      };
      
      class SDL2_t
        : public subsystem_base_t
      {
        using dtor_hook_t  = std::function<void()>;
        using dtor_hooks_t = std::forward_list<dtor_hook_t>;
        
        dtor_hooks_t _dtor_hooks;
        
        SDL_Window*   _window;
        //SDL_Renderer* _renderer;
        //SDL_Surface*  _surface;
        //SDL_Texture*  _texture;
        
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
          set_flag( "SDL.init_joystick", SDL_INIT_JOYSTICK );
#endif
          set_flag( "SDL.init_haptic"  , SDL_INIT_HAPTIC );
          set_flag( "SDL.init_gamecontroller", SDL_INIT_GAMECONTROLLER );
          set_flag( "SDL.init_events"        , SDL_INIT_EVENTS );
          set_flag( "SDL.init_everything"    , SDL_INIT_EVERYTHING );
          set_flag( "SDL.init_noparachute"   , SDL_INIT_NOPARACHUTE );
          
          const auto r = SDL_Init( flag );
          if ( r == -1 )
            throw sdl2_runtime_error_t( std::string("SDL_Init failed. return value: -1" ) );
          
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
            flag |= SDL_WINDOW_RESIZABLE;
          if ( not get_bool("visible") )
            flag |= SDL_WINDOW_HIDDEN;
          if ( not get_bool("decorated") )
            flag |= SDL_WINDOW_BORDERLESS;
          if ( get_bool("SDL.window_fullscreen") )
            flag |= SDL_WINDOW_FULLSCREEN;
          if ( get_bool("SDL.window_fullscreen_desktop") )
            flag |= SDL_WINDOW_FULLSCREEN_DESKTOP;
          if ( get_bool("SDL.window_opengl") )
            flag |= SDL_WINDOW_OPENGL;
          if ( get_bool("SDL.window_minimized") )
            flag |= SDL_WINDOW_MINIMIZED;
          if ( get_bool("SDL.window_maximized") )
            flag |= SDL_WINDOW_MAXIMIZED;
          if ( get_bool("SDL.window_input_grabbed") )
            flag |= SDL_WINDOW_INPUT_GRABBED;
#if SDL_VERSION_ATLEAST( 2 , 0 , 1 )
          if ( get_bool("SDL.window_allow_highdpi") )
            flag |= SDL_WINDOW_ALLOW_HIGHDPI;
#endif
          
          const auto window = _window
            = SDL_CreateWindow
              ( ps.get("title" , dps.get<std::string>("title") ).data()
              , get_int("x")
              , get_int("y")
              , get_int("width" )
              , get_int("height")
              , flag
              );
          
          if ( not window )
            throw sdl2_runtime_error_t
            ( "SDL_CreateWindow failed. window is nullptr." );
          
          _dtor_hooks.emplace_front( [ window ]
          {
            SDL_DestroyWindow( window );
          });
          
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
        }
        
        auto initialize_joystick() -> void
        {
#ifndef EMSCRIPTEN
          const auto number_of_joysticks = SDL_NumJoysticks();
          
          for ( auto index_of_joystick = 0; index_of_joystick < number_of_joysticks; ++index_of_joystick )
          {
            const auto joystick = SDL_JoystickOpen( index_of_joystick );
            
            joystick_state_name( index_of_joystick, SDL_JoystickNameForIndex( index_of_joystick ) );
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
              if ( SDL_JoystickGetAttached( joystick ) )
                SDL_JoystickClose( joystick );
            });
          }
#endif
        }
        
        auto process_events() -> void
        {
          SDL_Event e;
          
          bool has_key_event = false;
          std::int32_t wheel_event_dx = 0;
          std::int32_t wheel_event_dy = 0;
          
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
              case SDL_MOUSEWHEEL:
                wheel_event_dx = e.wheel.x;
                wheel_event_dy = e.wheel.y;
                break;
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
              case SDL_JOYDEVICEADDED:
              case SDL_JOYDEVICEREMOVED:
                break;
#endif
            }
          
          if ( has_key_event )
            process_events_keyevent();
          
          pointing_states_wheel( { wheel_event_dx, wheel_event_dy } );
        }
        
        auto process_events_keyevent() -> void
        {
          using sdl_key_states_t = const std::uint8_t*;
          sdl_key_states_t sdl_key_states = SDL_GetKeyboardState(nullptr);
          for ( auto n = 0; n < 255; ++n)
            keyboard_state( n, bool(sdl_key_states[n]) );
        }
        
      public:
        
        ~SDL2_t() override
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
          // https://wiki.libsdl.org/SDL_Init?highlight=%28%5CbCategoryInit%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
          ps.put( "SDL.init_timer"          , false );
          ps.put( "SDL.init_audio"          , false );
          ps.put( "SDL.init_video"          , true  );
          ps.put( "SDL.init_joystick"       , true  );
          ps.put( "SDL.init_haptic"         , false );
          ps.put( "SDL.init_gamecontroller" , true  );
          ps.put( "SDL.init_events"         , true  );
          ps.put( "SDL.init_everything"     , false );
          ps.put( "SDL.init_noparachute"    , false );
        }
        
        auto default_initialize_params_create_window(initialize_params_t& ps) const
          -> void
        {
          ps.put( "x"      ,   0 );
          ps.put( "y"      ,   0 );
          ps.put( "width"  , 320 );
          ps.put( "height" , 240 );
          ps.put( "title"  , "some other wonderland with SDL2" );
          
          // convert to SDL_WINDOW_RESIZABLE
          ps.put( "resizable" , true );
          // convert to SDL_WINDOW_HIDDEN
          ps.put( "visible"   , true );
          // convert to SDL_WINDOW_BORDERLESS
          ps.put( "decorated" , true );
          
          // SDL
          ps.put( "SDL.window_fullscreen"    , false );
          ps.put( "SDL.window_fullscreen_desktop", false);
          ps.put( "SDL.window_opengl"        , true  );
          ps.put( "SDL.window_minimized"     , false );
          ps.put( "SDL.window_maximized"     , false );
          ps.put( "SDL.window_input_grabbed" , false );
#if SDL_VERSION_ATLEAST( 2 , 0 , 1 )
          ps.put( "SDL.window_allow_highdpi" , false );
#endif
        }
        
        auto default_initialize_params() const
          -> initialize_params_t override
        {
          initialize_params_t ps;
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
          SDL_UpdateWindowSurface( _window );
          SDL_GL_SwapWindow( _window );
          process_events();
        }
        
        auto version() const
          -> version_t override
        { return { SDL_MAJOR_VERSION , SDL_MINOR_VERSION , SDL_PATCHLEVEL }; }
        
        auto name() const
          -> std::string override
        { return "SDL2"; }
        
      };
        
#ifndef WRP_WONDERLAND_SUBSYSTEM_T
#define WRP_WONDERLAND_SUBSYSTEM_T
      using subsystem_t = SDL2_t;
#endif
      
    }
  }
}