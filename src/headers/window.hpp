// [builder] implementation: window.cpp
#ifndef T_WINDOW
#define T_WINDOW

#include <SDL2/SDL.h>

using std::string;

namespace sdl {
  // ================================================
  struct WindowConfig {
    char* title;
    int x;
    int y;
    int width;
    int height;
  };

  // ================================================
  class Window {
    private:
    const WindowConfig& config;
    SDL_Window* window;

    public:
    Window(const WindowConfig& config);
    ~Window();

    // ================================================
    void create();

    // @temp
    void initSdl();
    void quitSdl();
  };
}


#endif
