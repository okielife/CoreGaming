#pragma once

#include <command.hpp>

class Game;
class Renderer;

struct GameState
{
    virtual ~GameState() = default;

    /**
     * The reset method should provide a way to reset all aspects of the current scene, back to the original state.
     * This would likely be called if a level was completely restarted or something.  Enemies would respawn, for
     * example. Right now it's not used anywhere.
     * @param game An instance of the parent Game class
     */
    virtual void reset(Game & game) {};

    /**
     * The reenter method should provide a way to set a level up based on re-entry.  Enemies would not respawn, for
     * example.  Right now it's not used anywhere.
     * @param game An instance of the parent Game class
     */
    virtual void reenter(Game & game) {};

    /**
     * The update() method should handle all aspects of this scene based on:
     *  time (cutscenes, actions)
     *  physics (gravity, updated positioning)
     *  logic (player and enemy movement)
     *  input (key press and key down events)
     * @param game An instance of the parent Game class
     * @param dt The current time between frames, for animation/physics calculations
     */
    virtual void update(Game & game, float dt) = 0;

    /**
     * The render() method for a scene should handle all drawing, by
     * using the methods available on the renderer class.
     * @param game An instance of the parent Game class
     * @param renderer The rendering engine being employed, currently a wrapper around SFML capabilities
     */
    virtual void render(Game & game, Renderer &renderer) = 0;

    virtual GameCommand pollCommand() {
        GameCommand c = pendingCommand;
        pendingCommand = GameCommand::None;
        return c;
    }

protected:
    GameCommand pendingCommand = GameCommand::None;
};
