#include <SDL2/SDL.h>
#include <string>

#include "headers/sdl.hpp"

using std::string;

namespace sdl {
  Sdl::~Sdl() {
    this->quit();
  }

  void Sdl::logError(string message) {
    const char* msg = message.c_str();
    SDL_Log(msg, SDL_GetError());
  }

  // ================================================
  void Sdl::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      this->logError("SDL_Init Error: %s\n");
    }
  }

  void Sdl::quit() {
    SDL_Quit();
  }
}
