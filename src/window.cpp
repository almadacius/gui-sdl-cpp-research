#include <SDL2/SDL.h>
#include "window.hpp"

sdl::Window::Window(const WindowConfig& config) {
  this->config = config;
}

sdl::Window::~Window() {
  SDL_DestroyWindow(this->window);
}

// ================================================
void sdl::Window::create() {
  WindowConfig* config = this->config;

  uint32 flags = 0;
  flags = SDL_WINDOW_SHOWN;

  this->window = SDL_CreateWindow(
    config.title,
    config.x,
    config.y,
    config.width,
    config.height,
    flags
  );
}

void sdl::Window::initSdl() {
  SDL_Init(SDL_INIT_VIDEO);
}

void sdl::Window::quitSdl() {
  SDL_Quit();
}
