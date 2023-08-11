#include <SDL2/SDL.h>

#include <cstdlib>
#include <string>

#include "lib/sdl-lib.hpp"

// ================================================
void cleanup() {
  sdlLib::cleanup();
}

// ================================================
void drawSquare() {
  SDL_Renderer* renderer = sdlLib::getRenderer();

  // red
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  // Draw a square
  SDL_Rect rect = { 200, 150, 100, 100 };
  SDL_RenderFillRect(renderer, &rect);
}

// ================================================
int main(int argc, char* argv[]) {
  atexit(cleanup);

  if (!sdlLib::init()) { return 1; }
  if (!sdlLib::create("test: DRAW SQUARE")) { return 1; }

  sdlLib::drawLoop(drawSquare);

  return 0;
}
