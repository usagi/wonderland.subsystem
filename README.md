# wonderland.subsystem

wonderland subsystem is C++ header-only library
 of commonize wrapper layer
 of a window management and an input event polling
 as GLFW3, GLFW2, SDL2, SDL1 and GLUT
 for standalone use and wonderland engine
 with PC(g++, clang++) and Emscripten(em++).

## warning

this is alpha version now.

developing in the master branch currently.

## currently support

- compiler
    - g++-4.8
    - clang++-3.2
    - em++-1.14

- subsystem
    - GLFW3
    - GLFW2

## features

- window and backend system management
    - commonized initialization for backends as GLFW3, GLFW2, SDL2, SDL1.
      - with RAII based automatic resource destructing.

- input management
    - commonized keyboard state (key-code convertible to USB HID Usage Page 9).
    - commonized pointing state
        - buttons : bool
        - wheel   : glm::vec2
        - position: glm::vec2
    
## dependancy

- [Boost.PropertyTree](http://www.boost.org/doc/libs/1_55_0/doc/html/property_tree.html)
- [glm](https://github.com/g-truc/glm)
- [Sprout](https://github.com/bolero-MURAKAMI/Sprout)

- optional (need one of these)
    - [GLFW3](http://www.glfw.org/)
    - GLFW2
    - [SDL2](http://www.libsdl.org/)
    - SDL1

## can't supporting feature list

- GLFW3
    - [joystcik hat-switch](https://github.com/glfw/glfw/issues/278)
    - joystick ball
    - joystcik name
- GLFW2
    - joystcik hat-switch
    - joystick ball
    - joystcik name
    - pointing device wheel dx
- SDL2
    - pointing device wheel dx
- SDL1 (1.2 and 1.3)
    - pointing device wheel dx dy
    - opengl core profile initialization

- Emscripten
    - [pointing device wheel dy reversed](https://github.com/kripken/emscripten/issues/2303)
    - game controller device is not supported
        - hint: [HTML5 Gamepad API](https://dvcs.w3.org/hg/gamepad/raw-file/default/gamepad.html#gamepad-interface) is not support common web-browser in currently

## plan to supporting list

- [plan to version 2.](https://github.com/usagi/wonderland.subsystem/issues/20)
    - GLUT + GLEW ( only for PC )
    - EGL + original-input-impl ( only for Web )
    - QtOpenGL

## backend API documentation link

- GLFW3 http://www.glfw.org/docs/3.0/
- GLFW2 http://www.glfw.org/GLFWReference27.pdf
- SDL2 https://wiki.libsdl.org/APIByCategory
- SDL1 http://www.libsdl.org/release/SDL-1.2.15/docs/html/

## license

- GPLv3

## author

Usagi Ito <usagi@WonderRabbitProject.net>
