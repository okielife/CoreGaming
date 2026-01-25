#pragma once

class Game;
class Renderer;

enum class SceneID
{
    Title,
    Level1,
    Pause,
    GameOver
};

struct SceneBase
{
    virtual ~SceneBase() = default;
    virtual void reset(Game & game) = 0;
    virtual void reenter(Game & game) = 0;
    virtual void update(Game & game, float dt) = 0;
    virtual void render(Game & game, Renderer &renderer) = 0;
    bool done = false;
};
