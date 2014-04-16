// for showing an initialize setting
#include <iostream>
#include <boost/property_tree/ini_parser.hpp>

#ifdef EMSCRIPTEN
  #include <emscripten/emscripten.h>
#endif

// define or take a compiler option: c++ ... -DWRP_WONDERLAND_SUBSYSTEM_GLFW3 main.cxx
//#define WRP_WONDERLAND_SUBSYSTEM_GLFW3
//#define WRP_WONDERLAND_SUBSYSTEM_GLFW2

// include subsystem
#include "subsystem.hxx"

int main()
{
  // using
  using wonder_rabbit_project::wonderland::subsystem::subsystem_t;
  using wonder_rabbit_project::wonderland::subsystem::key;
  
  // generate the subsystem
  auto subsystem = std::make_shared<subsystem_t>();
  
  // get initialize params ( not need if initilize with default settings )
  auto ips = subsystem -> default_initialize_params();
  
  // print ips in INI(1)
  std::cerr << "\n -- print ips in INI(1) -- \n";
  boost::property_tree::write_ini(std::cerr, ips);
  
  // change title
  ips.put
    ("title"
    , std::string("hello, subsystem ") + subsystem->name()
      + " version " + subsystem->version().to_string()
    );
 
  // print ips in INI(2)
  std::cerr << "\n -- print ips in INI(2) -- \n";
  boost::property_tree::write_ini(std::cerr, ips);
  
  // initialize the subsystem
  subsystem -> initialize( std::move(ips) );
  
  // invoke world pattern 1: consign main-loop to subsystem
  
  // set your world update code
  subsystem -> update_functors.emplace_front( [&subsystem]
  {
    /* do update your world */
    for ( auto key = 0; key < 255; ++key )
      if ( subsystem -> keyboard_state( key ) )
        std::cerr << key << " ";
    if ( subsystem -> keyboard_state< key::escape >() )
      subsystem -> to_continue( false );
  } );
  
  // set your world render code
  subsystem -> render_functors.emplace_front( []{ /* do render your world */ } );
  
  // invoke your world
  subsystem -> invoke();

  // invoke world pattern 2: original main-loop system with use subsystem
  /*
#ifdef EMSCRIPTEN  
  emscripten_set_main_loop( []
#else
  do
#endif
  {
    subsystem -> before_update();
    
    // do update world
    { }
    
    subsystem -> after_update();
    
    subsystem -> before_render();
    
    // do render with GL(glXxx)
    { }
    
    subsystem -> after_render();
  }
#ifdef EMSCRIPTEN  
  , 0, 1);
#else
  while ( subsystem -> to_continue );
#endif
  */
  
}