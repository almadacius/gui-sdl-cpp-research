#ifndef T_SDLLIB
#define T_SDLLIB

#include <SDL2/SDL.h>
#include <functional>

using std::function;
using std::string;

// ================================================
namespace sdlLib {
  struct State {
    bool init;
    SDL_Window* window;
    SDL_Renderer* renderer;
  };

  State state;

  // ================================================
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

  void logError(string text) {
    if(text == "") {
      text = "SDL_Init Error: %s\n";
    }
    SDL_Log(text.c_str(), SDL_GetError());
  }

  // ================================================
  SDL_Renderer* getRenderer() {
    return state.renderer;
  }

  // ================================================
  bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      sdlLib::logError("Error [SDL_Init]: %s\n");
      return false;
    }
    state.init = true;
    return true;
  }

  bool createWindow(string title) {
    if(title == "") {
      title = "window: test";
    }
    SDL_Window* window = SDL_CreateWindow(
      title.c_str(),
      0,
      0,
      800,
      600,
      SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
      sdlLib::logError("Error [SDL_CreateWindow]: %s\n");
      return false;
    }
    state.window = window;
    return true;
  }

  bool createWindow() {
    return sdlLib::createWindow("");
  }

  bool createRenderer() {
    SDL_Window* window = state.window;
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
      sdlLib::logError("Error [SDL_CreateRenderer]: %s\n");
      return false;
    }
    state.renderer = renderer;
    return true;
  }

  // ================================================
  bool create(string windowTitle) {
    if(!sdlLib::createWindow(windowTitle)){
      return false;
    }
    if(!sdlLib::createRenderer()) {
      return false;
    }
    return true;
  }

  // ================================================
  void drawLoop(function<void()> drawStuff) {
    SDL_Renderer* renderer = sdlLib::getRenderer();
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
      drawStuff();

      // Render modification
      SDL_RenderPresent(renderer);
    }
  }
}

#endif
