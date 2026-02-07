#pragma once

class Game;
class Renderer;

// TODO: Add a basic fighting game with animated characters and sprite sheets, also demonstrating better HUD

/**
 * An enumerated list of known scenes.  I imagine this changing drastically once this is no longer just ap prototype
 * of a bunch of game types.
 */
enum class SceneID
{
    None,
    Title,
    GridShow,
    WizardSpells,
    Platformer,
    BulletHell,
    Maze,
    // Pause,
    // GameOver,
    Exit,
};

struct SceneBase
{
    virtual ~SceneBase() = default;

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

    /**
     * A flag indicating that this scene is complete.  When this is set, the
     * nextScene members variable must be set to the ID so that game knows
     * what to start next.
     */
    bool done = false;

    /**
     * The scene that should be created once this scene is over.  Set this to the right
     * ID and set the done member variable to true and the game should switch scenes.
     */
    SceneID nextScene = SceneID::None;
};
