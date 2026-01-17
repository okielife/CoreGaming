#pragma once
#include "../platform/platform.h"
#include "../engine/camera.h"
#include "../engine/renderer.h"

class Platform;

class Game {
public:
    explicit Game(Platform& platform);
    void update(float dt);
    void render();

private:
    Platform& platform_;
    Renderer& renderer_;
    Input& input_;
    Camera camera_;

    float playerX_{100};
    float playerY_{100};
    float speed_{200};
};
