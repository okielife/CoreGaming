#pragma once

#include "level1.h"

class Game;
class Renderer;

struct SceneTitle : SceneBase
{
    explicit SceneTitle(const Game & game);
    ~SceneTitle() override = default;
    void reset(Game & game) final;
    void reenter(Game & game) final;
    void update(Game & game, float) final;
    void render(Game & game, Renderer & renderer) final;
};