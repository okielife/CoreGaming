#pragma once

#include <functional>

#include <SDL.h>

#include "renderer.h"
#include "input.h"

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
    Renderer renderer_;
    Input input_;
};
