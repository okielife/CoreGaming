#pragma once

#include <SDL.h>
#include <functional>

#include "sdl_renderer.h"
#include "sdl_input.h"

class Platform {
public:
    Platform(int width, int height, const char* title);
    ~Platform();
    void run(const std::function<void(float)>& frame);
    Renderer& renderer() { return renderer_; }
    Input& input() { return input_; }

private:
    bool running_{true};
    SDL_Window* window_{nullptr};
    SDL_Renderer* sdlRenderer_{nullptr};
    SDLRenderer renderer_;
    SDLInput input_;
};
