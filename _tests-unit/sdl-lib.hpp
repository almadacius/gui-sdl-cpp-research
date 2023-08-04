#ifndef T_SDLLIB
#define T_SDLLIB

#include <SDL2/SDL.h>
#include <functional>

using std::function;

// ================================================
namespace sdlLib {
  bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      SDL_Log("SDL_Init Error: %s\n", SDL_GetError());
      return false;
    }
    return true;
  }

  SDL_Window* createWindow() {
    SDL_Window* window = SDL_CreateWindow(
      "Square Renderer",
      0,
      0,
      800,
      600,
      SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
      SDL_Log("SDL_CreateWindow Error: %s\n", SDL_GetError());
      SDL_Quit();
      return NULL;
    }

    return window;
  }

  SDL_Renderer* createRenderer(SDL_Window* window) {
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
      SDL_Log("SDL_CreateRenderer Error: %s\n", SDL_GetError());
      SDL_DestroyWindow(window);
      SDL_Quit();
      return NULL;
    }

    return renderer;
  }

  void cleanup(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
  }

  void drawLoop(SDL_Renderer* renderer, function<void(SDL_Renderer*)> drawStuff) {
    bool isRunning = true;

    while(isRunning) {
      SDL_Event event;

      if(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
          isRunning = false;
        }
      }

      // white
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      // Clear screen
      SDL_RenderClear(renderer);

      // render stuff
      drawStuff(renderer);

      // Render modification
      SDL_RenderPresent(renderer);
    }
  }
}

#endif
