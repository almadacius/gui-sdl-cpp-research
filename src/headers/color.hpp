// [builder] implementation: color.cpp
#ifndef T_COLOR
#define T_COLOR

#include <SDL2/SDL.h>

namespace sdl {

  class Color {
    public:

    Uint8 r = 0;
    Uint8 g = 0;
    Uint8 b = 0;
    Uint8 a = 255;

    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    Color(Uint8 r, Uint8 g, Uint8 b);
  };

}

#endif
