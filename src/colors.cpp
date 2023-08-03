#include <string>

#include "headers/colors.hpp"

using std::string;

namespace sdl {
  std::map<std::string, Color*> colors = {
    {"black",  new Color(0,0,0)},
    {"white",  new Color(255,255,255)},
    {"red",  new Color(255,0,0)},
    {"blue",  new Color(0,255,0)},
    {"green",  new Color(0,0,255)},
    {"cyan",  new Color(0,255,255)},
    {"yellow",  new Color(255,255,0)},
    {"magenta",  new Color(255,0,255)}
  };
}
