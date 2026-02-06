#pragma once

class Game;
class Renderer;

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
    virtual void reset(Game & game) {};
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
    virtual void render(Game & game, Renderer &renderer) = 0;
    bool done = false;
    SceneID nextScene = SceneID::None;
};
