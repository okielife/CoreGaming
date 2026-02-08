#pragma once

#include <scenes/RoomBase.hpp>
#include <camera.hpp>
#include <drawables.hpp>

struct RoomPlatformer : RoomBase
{
    void update(Game & game, float dt) final;
    void render(Game & game, Renderer & renderer) final;
    Rect player {.w = 30, .h  = 40, .color = sf::Color::Blue};
    Transform playerTransform {.x = 100, .y = 150};
    Rect platform1 {.w = 200, .h = 20, .color = sf::Color(120, 120, 120)};
    static constexpr Transform platform1Transform = {.x = 50, .y = 300};
    Rect platform2 {.w = 200, .h = 20, .color = sf::Color(120, 120, 120)};
    static constexpr Transform platform2Transform = {.x = 400, .y = 230};
    Rect platform3 {.w = 150, .h = 20, .color = sf::Color(120, 120, 120)};
    static constexpr Transform platform3Transform = {.x = 850, .y = 380};
    Rect goalPlatform {.w = 100, .h = 2, .color = sf::Color::Green};
    static constexpr Transform goalPlatformTransform = {.x = 1160, .y = 320};
    Text message {};
    Transform messageTransform;

    float velocityY = 0.f;
    bool grounded = false;
    Camera camera {.y = WINDOW_HEIGHT / 2.0};
};
