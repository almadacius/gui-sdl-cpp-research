// [builder] implementation: window.cpp
#ifndef T_WINDOW
#define T_WINDOW

#include <SDL2/SDL.h>
#include <string>

#include "headers/renderer.hpp"

using std::string;

namespace sdl {
  // ================================================
  /*
    flags:
      - SDL_WINDOWPOS_UNDEFINED
      - SDL_WINDOWPOS_CENTERED
  */
  struct WindowConfig {
    string title;
    int x = 0;
    int y = 0;
    int width = 800;
    int height = 600;
  };

  // ================================================
  class Window {
    public:
    const WindowConfig& config;
    SDL_Window* window;
    Renderer* renderer;

    Window(const WindowConfig& config);
    ~Window();

    // ================================================
    void create();
    void createRenderer();
  };
}

#endif
