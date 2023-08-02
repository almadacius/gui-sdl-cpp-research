#include <SDL2/SDL.h>

#include "headers/sdl.hpp"
#include "headers/renderer.hpp"
#include "headers/color.hpp"

// ================================================
using Sdl = sdl::Sdl;
using std::function;

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

  void Renderer::clear() {
    SDL_RenderClear(this->renderer);
  }

  void Renderer::render() {
    SDL_RenderPresent(this->renderer);
  }

  void Renderer::setColor(Color* color) {
    SDL_SetRenderDrawColor(
      this->renderer,
      color->r,
      color->g,
      color->b,
      color->a
    );
  }

  // ================================================
  void Renderer::loop(function<void()> handler) {
    bool isRunning = true;

    while(isRunning) {
      SDL_Event event;

      if(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
          isRunning = false;
        }
      }

      this->clear();

      handler();

      this->render();
    }
  }
}
