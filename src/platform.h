#pragma once

#include "game.h"
#include "renderer.h"
#include "input.h"

struct SDL_Window;
struct SDL_Renderer;

/**
 * @file platform.h
 * Responsibilities of platform:
 * - SDL init / shutdown
 * - Window creation
 * - Event polling
 * - Keyboard/controller input
 * - Audio device management
 * - File IO paths (asset root, save dir)
 *
 * No other directory should have \#include SDL stuff
 * @ingroup platform
*/

/*
*Owns system resources

Window
SDL_Renderer
SDL init / shutdown
Event loop timing
*/

class Game;

class Platform {
public:
    Platform(int width, int height, const char* title);
    ~Platform();
    void run(Game & game);
    Input& input() { return input_; }
    Renderer * renderer_;
    Input input_;
    AudioManager audio_;

private:
    bool running_{true};
    SDL_Window* window_{nullptr};
    SDL_Renderer* sdlRenderer_{nullptr};
};
