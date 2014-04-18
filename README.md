# wonderland.subsystem

wonderland subsystem is commonize wrapper layer
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

## dependancy

- Boost.PropertyTree

- optional (need one of these)
    - GLFW3
    - GLFW2
    - SDL2
    - SDL1

## subsystem cannot supporting feature list

- GLFW3
- GLFW2
    - pointing device wheel dx
- SDL2
    - pointing device wheel dx
- SDL1
    - pointing device wheel dx dy
    
## license

- GPLv3

## author

Usagi Ito <usagi@WonderRabbitProject.net>
