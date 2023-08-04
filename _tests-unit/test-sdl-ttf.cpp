#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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

void loop(SDL_Renderer* renderer) {
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
    drawSquare(renderer);

    // Render modification
    SDL_RenderPresent(renderer);
  }
}

// ================================================
int main(int argc, char* argv[]) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("SDL_Init Error: %s\n", SDL_GetError());
    return 1;
  }

  // Create a window
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
    return 1;
  }

  // Create a renderer
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    SDL_Log("SDL_CreateRenderer Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  loop(renderer);

  // Cleanup and quit
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();

  return 0;
}
