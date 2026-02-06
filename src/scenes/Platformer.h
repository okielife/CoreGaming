#pragma once

#include <scenes/base.h>

struct Camera;
class Game;
class Renderer;

constexpr float gravity = 1800.f;
constexpr float jumpSpeed = 650.f;

struct PlatformData {float width, height, xLeft, yTop;};  // for now just basically a rectangle

struct ScenePlatformer : SceneBase
{
    ScenePlatformer();
    ~ScenePlatformer() override = default;
    void reset(Game & game) final;
    void reenter(Game & game) final;
    void update(Game & game, float dt) final;
    void render(Game & game, Renderer & renderer) final;
    sf::RectangleShape player;
    std::vector<sf::RectangleShape> platforms;
    sf::RectangleShape goalPlatform;
    float velocityY = 0.f;
    bool grounded = false;
    bool won = false;
    Camera camera;
};
