#pragma once

#include <camera.hpp>
#include <rooms/RoomBase.hpp>

struct RoomGridShow : RoomBase
{
    void update(Game & game, float dt) final;
    void render(Game & game, Renderer & renderer) final;
    Rect playerRect {.w = 28.0, .h = 28.0, .color = {200, 80, 80, 255}};
    Transform playerTransform {.x = 100, .y = 100};
    Rect mapGridRect {.w = 32, .h = 32, .outlineColor = {40, 40, 40, 255}, .outlineThickness = 1.0};
    Transform mapGridTransform {.x = 0, .y = 0};
    Text instructions {.text = "Use Arrow Keys; ESC to exit", .color = sf::Color::Red};
    Transform instructionsTransform {.x = 20, .y = 50};
    Text coordinates {.text="", .color = sf::Color::Red};
    Transform coordinatesTransform {.x = 20, .y = 80, .rotation=10, .sx = 0.5};
    Camera camera;
    float swordCooldownMS = 1.0f;   // seconds
    float msSinceLastSword = swordCooldownMS; // start "ready"
};
