#include <SDL2/SDL.h>

#include "headers/sdl.hpp"
#include "headers/renderer.hpp"
#include "headers/window.hpp"

using Sdl = sdl::Sdl;

// ================================================
namespace sdl {
  Window::Window(const WindowConfig& config) : config(config) {}

  Window::~Window() {
    SDL_DestroyWindow(this->window);
  }

  // ================================================
  void Window::createRenderer() {
    Renderer* renderer = new Renderer();
    this->renderer = renderer;

    renderer->create(this->window);
  }

  void Window::create() {
    const WindowConfig& config = this->config;

    Uint32 flags = 0;
    flags = SDL_WINDOW_SHOWN;

    this->window = SDL_CreateWindow(
      config.title.c_str(),
      config.x,
      config.y,
      config.width,
      config.height,
      flags
    );

    // @todo - throw
    if (this->window == NULL) {
      Sdl* sdl = new Sdl();
      sdl->logError("SDL_CreateWindow Error: %s\n");
    }

    this->createRenderer();
  }
}
