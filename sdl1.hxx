#pragma once

#include <forward_list>

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
          set_flag( "SDL.init_cdrom", SDL_INIT_CDROM );
          set_flag( "SDL.init_joystick", SDL_INIT_JOYSTICK );
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
        }
        
        auto initialize_set_caption(initialize_params_t ps)
          -> void const
        {
          initialize_params_t dps;
          default_initialize_params_set_caption(dps);
          
          SDL_WM_SetCaption( ps.get("title" ,dps.get<std::string>("title")).data(), nullptr );
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
            }
          
          if ( has_key_event )
            process_events_keyevent();
        }
        
        auto process_events_keyevent() -> void
        {
          using sdl_key_states_t = const std::uint8_t*;
          sdl_key_states_t sdl_key_states = SDL_GetKeyState(nullptr);
          for ( auto n = SDLK_FIRST; n < SDLK_LAST; ++n)
          {
            if ( sdl_key_states[n] )
              std::cerr << "*** in " << n << " ***";
            keyboard_state( key_code_from_sdl1(n), bool(sdl_key_states[n]) );
          }
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
        }
        
        auto after_render()
          -> void override
        {
          SDL_UpdateRect( _surface, 0, 0, 0, 0 );
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