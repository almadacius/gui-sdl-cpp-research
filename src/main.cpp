#include <map>
#include <SDL2/SDL.h>

#include "headers/sdl.hpp"
#include "headers/window.hpp"
#include "headers/color.hpp"
#include "headers/colors.hpp"

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
    using sdl::colors;

    renderer->setColor(colors["white"]);
    renderer->clear();

    renderer->setColor(colors["cyan"]);
    SDL_Rect rect = { 200, 150, 100, 100 };
    SDL_RenderFillRect(renderer->renderer, &rect);

    renderer->setColor(colors["yellow"]);
    SDL_Rect rect2 = { 400, 150, 100, 100 };
    SDL_RenderFillRect(renderer->renderer, &rect2);
  });

  return 0;
}
