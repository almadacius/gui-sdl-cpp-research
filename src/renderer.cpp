#include <SDL2/SDL.h>

#include "headers/sdl.hpp"
#include "headers/renderer.hpp"

using Sdl = sdl::Sdl;

// ================================================
namespace sdl {
  Renderer::Renderer() {
    RendererConfig* config = new RendererConfig();
    this->config = config;
  }

  Renderer::Renderer(RendererConfig* config) {
    this->config = config;
  }

  Renderer::~Renderer() {
    SDL_DestroyRenderer(this->renderer);
  }

  // ================================================
  void Renderer::create(SDL_Window* window) {
    const RendererConfig* config = this->config;

    Uint32 flags = 0;
    flags = SDL_RENDERER_ACCELERATED;

    this->renderer = SDL_CreateRenderer(
      window,
      config->index,
      flags
    );

    // @todo - throw
    if (this->renderer == NULL) {
      Sdl* sdl = new Sdl();
      sdl->logError("SDL_CreateRenderer Error: %s\n");
    }
  }
}
