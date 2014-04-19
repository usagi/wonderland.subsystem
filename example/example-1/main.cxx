#include <chrono>
#include <thread>
#include <iostream>
#include <iomanip>
#include <boost/property_tree/ini_parser.hpp>

#ifdef EMSCRIPTEN
  #include <emscripten/emscripten.h>
#endif

// define or take a compiler option: c++ ... -DWRP_WONDERLAND_SUBSYSTEM_GLFW3 main.cxx
//#define WRP_WONDERLAND_SUBSYSTEM_GLFW3
//#define WRP_WONDERLAND_SUBSYSTEM_GLFW2

// include subsystem
#include <wonder_rabbit_project/wonderland.subsystem.hxx>

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
  const auto keyboard_test = [ &subsystem ]
  {
    auto key_counter = 0;
    for ( auto key = 0; key < 255; ++key )
      if ( subsystem -> keyboard_state( key ) )
      {
        ++key_counter;
        std::cerr << key << " ";
      }
    
    if ( key_counter )
      std::cerr << "\n";
  };
  
  const auto pointing_test = [ &subsystem ]
  {
    auto button_counter = 0;
    for ( auto button = 0; button < 8; ++button )
      if ( subsystem -> pointing_states_button( button ) )
      {
        ++button_counter;
        std::cerr << "pointing_button[" << button << "] ";
      }
    
    if ( button_counter )
    {
      const auto position = subsystem -> pointing_states_position();
      std::cerr
        << " with position("
        << position.x << ", "
        << position.y << ")\n";
    }

    const auto wheel = subsystem -> pointing_states_wheel();
    if ( wheel.x not_eq 0 )
      std::cerr << "wheel-dx: " << wheel.x << "\n";
    if ( wheel.y not_eq 0 )
      std::cerr << "wheel-dy: " << wheel.y << "\n";
  };
  
  const auto joystick_test = [ &subsystem ]
  {
    for ( const auto joystick : subsystem -> joysticks_states() )
    {
      const auto& digitals = joystick.digitals();
      const auto& analogs  = joystick.analogs();
      const auto& balls    = joystick.balls();
      const auto& hats     = joystick.hats();
      
      if
      (  std::any_of(std::begin(digitals), std::end(digitals), [](const bool v){ return v; } ) 
      or std::any_of(std::begin(hats), std::end(hats), [](const glm::vec2& v){ return v not_eq glm::vec2(); } )
      )
      {
        std::cerr << joystick.name() << ": D{ ";
        for ( const auto digital : digitals )
          std::cerr << digital << " ";
        std::cerr << "} A{ ";
        for ( const auto analog  : analogs )
          std::cerr << std::setw(5) << std::right << std::setprecision(2) << std::fixed << analog << " ";
        std::cerr << "} B{ ";
        for ( const auto ball    : balls )
          std::cerr << "(" << ball.x << "," << ball.y << ") ";
        std::cerr << "} H{ ";
        for ( const auto hat     : hats )
          std::cerr << "(" << hat.x  << "," << hat.y  << ") ";
        std::cerr << "}\n";
        
      }
    }
  };
  
  const auto esc_to_exit = [ &subsystem ]
  {
    if ( subsystem -> keyboard_state< key::escape >() )
      subsystem -> to_continue( false );
  };
  
  subsystem -> update_functors.emplace_front( keyboard_test );
  subsystem -> update_functors.emplace_front( pointing_test );
  subsystem -> update_functors.emplace_front( joystick_test );
  subsystem -> update_functors.emplace_front( esc_to_exit   );
  subsystem -> update_functors.emplace_front( []
  {
    // do update your world
  } );
  
  // set your world render code
//#ifndef EMSCRIPTEN
  const auto adjust_wait = [ ]
  {
    static auto before = std::chrono::high_resolution_clock::now();
    const auto elapsed = std::chrono::high_resolution_clock::now() - before;
    const auto wait = std::chrono::milliseconds(100) - elapsed;
    std::this_thread::sleep_for(wait);
    before = std::chrono::high_resolution_clock::now();
  };
//#endif
  
  subsystem -> render_functors.emplace_front( []
  {
    // do render your world
  } );
//#ifndef EMSCRIPTEN
  subsystem -> render_functors.emplace_front( adjust_wait );
//#endif
  
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