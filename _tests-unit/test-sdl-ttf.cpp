#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <cstdlib>
#include <string>

#include "lib/sdl-lib.hpp"
#include "lib/sdl-ttf-lib.hpp"
#include "lib/fs.hpp"

using std::string;

// ================================================
void cleanup() {
  sdlTtfLib::cleanup();
  sdlLib::cleanup();
}

// ================================================
void update() {
  // black
  sdlTtfLib::setColor({ 0, 0, 0 });
  sdlTtfLib::updateText("this is some rendered text");
}

void draw(SDL_Renderer* renderer) {
  sdlTtfLib::render();
}

// ================================================
int main(int argc, char* argv[]) {
  atexit(cleanup);

  if (!sdlLib::init() != 0) { return 1; }
  if (!sdlTtfLib::init() != 0) { return 1; }

  SDL_Window* window = sdlLib::createWindow();
  if (window == NULL) { return 1; }

  SDL_Renderer* renderer = sdlLib::createRenderer(window);
  if (renderer == NULL) { return 1; }

  // ================================================
  fs::init(argv);
  string fontPath = fs::getAssetPath("tanohe-sans-regular.ttf");

  if(!sdlTtfLib::loadFont(fontPath)){ return 1; };

  // ================================================
  update();
  sdlLib::drawLoop(renderer, draw);

  return 0;
}
