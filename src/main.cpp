#include <SDL2/SDL.h>

#include "headers/sdl.hpp"
#include "headers/window.hpp"
#include "headers/color.hpp"

using Sdl = sdl::Sdl;
using Color = sdl::Color;

// ================================================
int main(int argc, char* argv[]) {
  Sdl* sdl = new Sdl();
  sdl->init();

  sdl::WindowConfig config;
  config.title = "Square Renderer";

  sdl::Window* window = new sdl::Window(config);
  window->create();

  sdl::Renderer* renderer = window->renderer;
  renderer->loop([renderer](){
    renderer->setColor(new Color(200, 0, 0));
    renderer->clear();

    renderer->setColor(new Color(0, 0, 0));
    // Draw a square
    SDL_Rect rect = { 200, 150, 100, 100 };
    SDL_RenderFillRect(renderer->renderer, &rect);
  });

  return 0;
}
