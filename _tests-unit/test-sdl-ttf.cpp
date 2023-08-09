#include <SDL2/SDL.h>
#include <SDL_ttf.h>

#include "sdl-lib.hpp"

// ================================================
void drawSquare(SDL_Renderer* renderer) {
  // red
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  // Clear the window
  SDL_RenderClear(renderer);

  // Draw a square
  SDL_Rect rect = { 200, 150, 100, 100 };
  SDL_RenderFillRect(renderer, &rect);
}

// ================================================
int main(int argc, char* argv[]) {
  if (!sdlLib::init() != 0) { return 1; }

  SDL_Window* window = sdlLib::createWindow();
  if (window == NULL) { return 1; }

  SDL_Renderer* renderer = sdlLib::createRenderer(window);
  if (renderer == NULL) { return 1; }

  sdlLib::drawLoop(renderer, drawSquare);

  sdlLib::cleanup(window, renderer);

  return 0;
}
