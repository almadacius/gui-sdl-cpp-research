#ifndef T_SDLLIB
#define T_SDLLIB

#include <SDL2/SDL.h>
#include <functional>

using std::function;

// ================================================
namespace sdlLib {
  struct State {
    bool init;
    SDL_Window* window;
    SDL_Renderer* renderer;
  };

  State state;

  void cleanup() {
    if(state.window) {
      SDL_DestroyWindow(state.window);
    }
    if(state.renderer) {
      SDL_DestroyRenderer(state.renderer);
    }
    if(state.init) {
      SDL_Quit();
    }
  }

  // ================================================
  bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      SDL_Log("SDL_Init Error: %s\n", SDL_GetError());
      return false;
    }
    state.init = true;
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
      return NULL;
    }
    state.window = window;
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
    state.renderer = renderer;
    return renderer;
  }

  // ================================================
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
