#pragma once

#include "level1.h"

struct SceneTitle : SceneBase
{
    explicit SceneTitle(const Game & game);
    ~SceneTitle() override = default;
    void reset(Game & game) final;
    void reenter(Game & game) final;
    void update(Game & game, float dt) final;
    void render(Game & game) final;
    TextureID titleBackground_ = 0;
};