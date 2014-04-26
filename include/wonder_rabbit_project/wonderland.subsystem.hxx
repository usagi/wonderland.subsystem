#if not defined( WRP_WONDERLAND_SUBSYSTEM_GLFW3 ) \
 or not defined( WRP_WONDERLAND_SUBSYSTEM_GLFW2 ) \
 or not defined( WRP_WONDERLAND_SUBSYSTEM_SDL2 ) \
 or not defined( WRP_WONDERLAND_SUBSYSTEM_SDL1 )
  #ifndef EMSCRIPTEN
    #define WRP_WONDERLAND_SUBSYSTEM_GLFW3
  #else
    #define WRP_WONDERLAND_SUBSYSTEM_GLFW2
  #endif
#endif

#include <boost/scope_exit.hpp>

#include "wonderland.subsystem.detail/key.hxx"
#include "wonderland.subsystem.detail/key_helper.hxx"
#include "wonderland.subsystem.detail/subsystem_base.hxx"

#ifdef WRP_WONDERLAND_SUBSYSTEM_GLFW3
  #include "wonderland.subsystem.detail/glfw3.hxx"
#elif defined(WRP_WONDERLAND_SUBSYSTEM_GLFW2)
  #include "wonderland.subsystem.detail/glfw2.hxx"
#elif defined(WRP_WONDERLAND_SUBSYSTEM_SDL2)
  #include "wonderland.subsystem.detail/sdl2.hxx"
#elif defined(WRP_WONDERLAND_SUBSYSTEM_SDL1)
  #include "wonderland.subsystem.detail/sdl1.hxx"
#endif
