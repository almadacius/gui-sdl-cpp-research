#include "headers/color.hpp"

namespace sdl {
  Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
  }

  Color::Color(Uint8 r, Uint8 g, Uint8 b) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = 255;
  }
}
