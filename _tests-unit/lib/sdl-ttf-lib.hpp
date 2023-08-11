#ifndef T_SDLTTFLIB
#define T_SDLTTFLIB

#include <functional>
#include <filesystem>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL_ttf.h>

#include "sdl-lib.hpp"

using std::cout;
using std::endl;
using std::function;
using std::string;

// ================================================
namespace sdlTtfLib {
  struct State {
    bool init;
    TTF_Font* font;
    SDL_Color color;
    SDL_Texture* texture;
    SDL_Rect rect;
  };

  State state;

  // ================================================
  void cleanup() {
    if(state.texture) {
      SDL_DestroyTexture(state.texture);
    }
    if(state.font) {
      TTF_CloseFont(state.font);
    }
    if(state.init) {
      TTF_Quit();
    }
  }

  void logError(string name) {
    cout << "Error[" << name << "]: " << TTF_GetError() << endl;
  }

  // ================================================
  bool init() {
    if (TTF_Init() != 0) {
      logError("TTF_Init");
      return false;
    }
    state.init = true;
    return true;
  }

  bool loadFont(string fontPath) {
    cout << "using font: " << fontPath << endl;
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), 24);
    if (!font) {
      logError("TTF_OpenFont");
      return false;
    }
    state.font = font;
    return true;
  }

  // ================================================
  void setColor(SDL_Color color) {
    state.color = color;
  }

  void updateText(string text) {
    SDL_Renderer* renderer = sdlLib::state.renderer;

    SDL_Surface* surface = TTF_RenderText_Solid(
      state.font, text.c_str(), state.color
    );
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    state.texture = texture;

    SDL_Rect rect;
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    // "centering"
    rect.x = (800 - rect.w) / 2;
    rect.y = (600 - rect.h) / 2;
    state.rect = rect;
  }

  void render() {
    SDL_Renderer* renderer = sdlLib::state.renderer;

    SDL_RenderCopy(renderer, state.texture, NULL, &state.rect);
  }
}

#endif
