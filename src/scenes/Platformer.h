#pragma once

#include <array>
#include "base.h"

class Game;
class Renderer;

constexpr float gravity = 1800.f;
constexpr float jumpSpeed = 650.f;

struct ScenePlatformer : SceneBase
{
    ScenePlatformer();
    ~ScenePlatformer() override = default;
    void reset(Game & game) final;
    void reenter(Game & game) final;
    void update(Game & game, float dt) final;
    void render(Game & game, Renderer & renderer) final;
    sf::RectangleShape player;
    sf::RectangleShape startPlatform;
    sf::RectangleShape goalPlatform;
    float velocityY = 0.f;
    bool grounded = false;
    bool won = false;
};
