#include <SDL2/SDL.h>
#include "headers/sdl.hpp"

namespace sdl {
  void Sdl::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      SDL_Log("SDL_Init Error: %s\n", SDL_GetError());
    }
  }

  void Sdl::quit() {
    SDL_Quit();
  }
}
