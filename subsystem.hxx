#include <boost/scope_exit.hpp>

#include "key.hxx"
#include "key_helper.hxx"
#include "subsystem_base.hxx"

#ifdef WRP_WONDERLAND_SUBSYSTEM_GLFW3
  #include "glfw3.hxx"
#elif defined(WRP_WONDERLAND_SUBSYSTEM_GLFW2)
  #include "glfw2.hxx"
#elif defined(WRP_WONDERLAND_SUBSYSTEM_SDL2)
  #include "sdl2.hxx"
#elif defined(WRP_WONDERLAND_SUBSYSTEM_SDL1)
  #include "sdl1.hxx"
#elif defined(WRP_WONDERLAND_SUBSYSTEM_GLUT)
  #include "glut.hxx"
#endif
