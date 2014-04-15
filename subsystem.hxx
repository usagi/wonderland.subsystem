#include <boost/scope_exit.hpp>

#include "subsystem_base.hxx"

#ifdef WRP_WONDERLAND_SUBSYSTEM_GLFW3
  #include "glfw3.hxx"
#elif defined(WRP_WONDERLAND_SUBSYSTEM_GLFW2)
  #include "glfw2.hxx"
#endif
