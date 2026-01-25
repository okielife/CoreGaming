#pragma once

#include "base.h"
#include "../camera.h"

class Game;

struct SceneLevel1 : SceneBase
{
    ~SceneLevel1() override = default;
    void reset(Game & game) final;
    void reenter(Game & game) final;
    void update(Game & game, float dt_ms) final;
    void render(Game & game) final;
    float playerX_{100};
    float playerY_{100};
    float speed_{.2};  // think of it like pixels per millisecond
    Camera overheadCamera;

    float swordCooldownMS = 1000.0f;   // milliseconds
    float msSinceLastSword = swordCooldownMS; // start "ready"
};
