#pragma once

#include "base.h"
#include "../camera.h"

class Game;
class Renderer;

struct SceneGridShow : SceneBase
{
    ~SceneGridShow() override = default;
    void reset(Game & game) final;
    void reenter(Game & game) final;
    void update(Game & game, float dt) final;
    void render(Game & game, Renderer & renderer) final;
    float playerX_{100};
    float playerY_{100};
    float speed_{200};  // think of it like game units per second
    Camera overheadCamera;

    float swordCooldownMS = 1.0f;   // seconds
    float msSinceLastSword = swordCooldownMS; // start "ready"
};
