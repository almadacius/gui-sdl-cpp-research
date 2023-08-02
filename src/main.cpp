#include <SDL2/SDL.h>

#include "headers/sdl.hpp"
#include "headers/window.hpp"

using Sdl = sdl::Sdl;

// ================================================
void drawSquare(SDL_Renderer* renderer) {
  // Set the draw color (red in this case)
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  // Clear the window
  SDL_RenderClear(renderer);

  // Draw a square
  SDL_Rect rect = { 200, 150, 100, 100 };
  SDL_RenderFillRect(renderer, &rect);
}

void runDelay(int secs) {
  // Wait for a short moment
  int delay = secs * 1000;
  SDL_Delay(delay);
}

void loop(SDL_Renderer* renderer) {
  bool isRunning = true;

  // Infinite loop
  while(isRunning) {
    SDL_Event event;

    if(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
        isRunning = false;
      }
    }

    // Clear screen
    SDL_RenderClear(renderer);

    // render stuff
    drawSquare(renderer);

    // Render modification
    SDL_RenderPresent(renderer);
  }
}

// ================================================
int main(int argc, char* argv[]) {
  Sdl* sdl = new Sdl();
  sdl->init();

  sdl::WindowConfig config;
  config.title = "Square Renderer";

  sdl::Window* window = new sdl::Window(config);
  window->create();

  loop(window->renderer->renderer);

  return 0;
}
