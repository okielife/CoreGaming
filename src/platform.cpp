#include <filesystem>
#include <stdexcept>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "platform.h"
#include "renderer.h"

Platform::Platform(const int width, const int height, const char* title) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(SDL_GetError());
    }
    if (TTF_Init() == -1)
    {
        SDL_Log("TTF_Init failed: %s", TTF_GetError());
    }

    this->window_ = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!this->window_) {
        throw std::runtime_error(SDL_GetError());
    }

    this->sdlRenderer_ = SDL_CreateRenderer(this->window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!this->sdlRenderer_) {
        throw std::runtime_error(SDL_GetError());
    }

    // Now that we have SDL_Renderer*, rebind renderer_
    this->renderer_ = new Renderer(this->sdlRenderer_);
}

Platform::~Platform() {
    delete this->renderer_;
    SDL_DestroyRenderer(this->sdlRenderer_);
    SDL_DestroyWindow(this->window_);
    TTF_Quit();
    SDL_Quit();
}

void Platform::run(Game & game) {
    Uint32 last = SDL_GetTicks();

    //game.init(); as needed to load things like textures

    while (this->running_) {
        input_.beginFrame();

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            input_.update(e);
            if (e.type == SDL_QUIT)
            {
                this->running_ = false;
            }
        }

        input_.update();
        const auto now = SDL_GetTicks64();
        const auto dt_ms = static_cast<float>(now - last);
        last = now;

        game.frame(dt_ms);
        if (!game.running)
        {
            this->running_ = false;
        }
        SDL_RenderPresent(this->sdlRenderer_);
    }
}
