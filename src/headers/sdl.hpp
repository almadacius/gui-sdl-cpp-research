// [builder] implementation: sdl.cpp
#ifndef T_SDL
#define T_SDL

#include <SDL2/SDL.h>
#include <string>

using std::string;

namespace sdl {

  class Sdl {
    public:

    ~Sdl();

    void init();
    void quit();

    void logError(string message);
  };

}


#endif
