#include <SDL2/SDL.h>

class SDLWindow {
public:
    SDLWindow(const char* title, int x, int y, int width, int height) {
        window = SDL_CreateWindow(title, x, y, width, height, SDL_WINDOW_SHOWN);
    }

    ~SDLWindow() {
        SDL_DestroyWindow(window);
    }

    // Add more methods as needed, like handling events, resizing, etc.

private:
    SDL_Window* window;
};

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    // Use the SDLWindow class
    SDLWindow window("Square Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600);

    // Create the renderer, draw the square, etc.

    SDL_Quit();
    return 0;
}
