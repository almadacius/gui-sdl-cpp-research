#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("SDL_Init Error: %s\n", SDL_GetError());
    return 1;
  }

  // Create a window
  SDL_Window* window = SDL_CreateWindow("Square Renderer",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    800, 600,
    SDL_WINDOW_SHOWN
  );

  if (!window) {
    SDL_Log("SDL_CreateWindow Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  // Create a renderer
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    SDL_Log("SDL_CreateRenderer Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  // Set the draw color (red in this case)
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  // Clear the window
  SDL_RenderClear(renderer);

  // Draw a square
  SDL_Rect rect = { 200, 150, 100, 100 };
  SDL_RenderFillRect(renderer, &rect);

  // Present the renderer
  SDL_RenderPresent(renderer);

  // Wait for a short moment
  SDL_Delay(10000);

  // Cleanup and quit
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
