#pragma once
#include "platform.h"
#include "audio.h"
#include "input.h"
#include "renderer.h"
#include "camera.h"

class Platform;

class Game {
public:
    explicit Game(Platform& platform);
    ~Game();
    void frame(float dt);
    void update(float dt);
    void render();

private:
    Platform& platform_;
    Renderer& renderer_;
    Input& input_;
    Camera camera_;
    AudioManager audio;

    float playerX_{100};
    float playerY_{100};
    float speed_{200};
};
