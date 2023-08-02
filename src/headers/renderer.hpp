// [builder] implementation: renderer.cpp
#ifndef T_RENDERER
#define T_RENDERER

#include <SDL2/SDL.h>
#include <string>

using std::string;

namespace sdl {
  // ================================================
  /*
    flags:
    [https://wiki.libsdl.org/SDL2/SDL_RendererFlags]
    - SDL_RENDERER_SOFTWARE
    - SDL_RENDERER_ACCELERATED
    - SDL_RENDERER_PRESENTVSYNC
    - SDL_RENDERER_TARGETTEXTURE
  */
  struct RendererConfig {
    // -1 means the first one compatible with the flags
    int index = -1;
  };

  // ================================================
  class Renderer {
    public:
    RendererConfig* config;
    SDL_Window* window;
    SDL_Renderer* renderer;

    Renderer();
    Renderer(RendererConfig* config);
    ~Renderer();

    // ================================================
    void create(SDL_Window* window);
  };
}

#endif
