#include <filesystem>
#include <stdexcept>

#include "platform.h"
#include "renderer.h"

Platform::Platform(const int width, const int height, const char* title) : renderer_(nullptr) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(SDL_GetError());
    }

    window_ = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    if (!window_) {
        throw std::runtime_error(SDL_GetError());
    }

    sdlRenderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!sdlRenderer_) {
        throw std::runtime_error(SDL_GetError());
    }

    // Now that we have SDL_Renderer*, rebind renderer_
    renderer_ = Renderer(sdlRenderer_);
}

Platform::~Platform() {
    SDL_DestroyRenderer(sdlRenderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Platform::run(const std::function<void(float)>& frame) {
    Uint32 last = SDL_GetTicks();

    while (running_) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running_ = false;
        }

        input_.update();

        const Uint32 now = SDL_GetTicks();
        const float dt = static_cast<float>(now - last) / 1000.0f;
        last = now;

        frame(dt);

        SDL_RenderPresent(sdlRenderer_);
    }
}
