#pragma once

#include <SFML/Graphics.hpp>

#include "game.h"
#include "renderer.h"
#include "input.h"

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
class Renderer;

class Platform {
public:
    Platform();
    void run(Game & game);
    Input& input() { return input_; }
    Renderer renderer;
    Input input_;
    AudioManager audio_;

private:
    sf::RenderWindow window;
    sf::Clock clock;
};
