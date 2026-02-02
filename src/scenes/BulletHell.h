#pragma once

#include <SFML/Graphics.hpp>

#include "base.h"

class Game;
class Renderer;

struct Bullet {
    sf::RectangleShape shape;
    float speed;
};

constexpr float playerSpeed = 300.f;

// Bullets
constexpr float bulletSpeedMin = 200.f;
constexpr float bulletSpeedMax = 400.f;
constexpr float bulletSpawnInterval = 0.08f;
constexpr float bulletSpawnDuration = 4.f;

class SceneBulletHell : public SceneBase {
public:
    SceneBulletHell();
    void reset(Game & game) override {};
    void reenter(Game & game) override {};
    void update(Game & game, float dt) override;
    void render(Game & game, Renderer &renderer) override;
private:
    sf::RectangleShape player;
    std::vector<Bullet> bullets;
    bool lost = false;
    bool won = false;
    sf::Clock spawnClock;
    sf::Clock lifetimeClock;
    sf::Clock frameClock;
};
