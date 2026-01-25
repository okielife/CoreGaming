#pragma once

#include <map>

#include "audio.h"
#include "input.h"
#include "renderer.h"
#include "scenes/base.h"

class Platform;
class Renderer;

/**
 * @file game.h
 * @brief The primary driver for the game itself.
 *
 * This file contains game logic and ownership of overall game assets, such as scenes, player, etc.
 * When you want to develop on the game logic itself, this is probably the right place to start.
 * This file does not directly inherit anything SDL, but instead relies on wrapper managers for
 * platform specific assets such as audio and window.
 *
 * @ingroup game
 */

/**
 * @brief Primary game class
 *
 * This class provides the game logic itself, as an owner of the player, scenes, and anything else
 * that needs a game-long lifetime.  The game can be thought of as a state engine that determines
 * the current game mode (title, gameplay, game over, pause, etc.).  The game class has no specific
 * SDL knowledge, but instead depends on wrapper managers to render, play audio, get input, and more.
 *
 * @ingroup game
 */
class Game {

public:
    /**
     * @brief The primary constructor for a game instance.
     *
     * This constructor takes references to the platform-layer managers for later access.
     * The constructor is responsible for instantiating the list of game scenes and
     * setting the initial scene state.
     *
     * @param input An input manager with methods to check for key presses and key down
     * @param audio An audio manager with methods for starting and stopping audio and sound effects
     */
    Game(Input& input, AudioManager& audio);

    /**
     * @brief Perform one frame update of the game.
     *
     * The game update() method consists of any game-level updates and then asking
     * the current scene to update.
     *
     * @param dt The floating point number of seconds since the last frame. Use this for calculations
     *              on movement speed and other physics as needed.
     */
    void update(float dt);

    /**
     * @brief Perform one frame render of the game.
     *
     * The game render() method consists of any game-level renders (maybe menus?) and then asking
     * the current scene to render.
     *
     * @param renderer A rendering manager with methods for drawing to the screen
     */
    void render(Renderer & renderer);

    /**
     * @brief Reference to platform input manager
     */
    Input& input;

    /**
     * @brief Reference to platform audio manager
     */
    AudioManager& audio;

    /**
     * A simple boolean to alert the platform system that we are done.
     * Could be used to go back to a main menu or clean things up before
     * closing down the platform.
     */
    bool running = true;

private:
    std::map<SceneID, std::unique_ptr<SceneBase>> scenes;
    SceneID currentSceneID;
    SceneBase * currentScene;  // non-owning pointer
};
