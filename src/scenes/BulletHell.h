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
constexpr float bulletWidth = 10.0f;
constexpr float bulletHeight = 5.0f;
constexpr float bulletSpeedMin = 200.f;
constexpr float bulletSpeedMax = 400.f;
constexpr float bulletSpawnInterval = 0.05f;
constexpr float bulletSpawnDuration = 4.f;
constexpr float actionWindowX = 200;
constexpr float actionWindowY = 100;
constexpr float actionWindowWidth = 400;
constexpr float actionWindowHeight = 400;
constexpr float playerWidth = 25.0;
constexpr float playerHeight = 25.0;

class SceneBulletHell : public SceneBase {
public:
    SceneBulletHell();
    void reset(Game & game) override {};
    void reenter(Game & game) override {};
    void update(Game & game, float dt) override;
    void render(Game & game, Renderer &renderer) override;
private:
    sf::RectangleShape player;
    sf::RectangleShape actionWindow;
    std::vector<Bullet> bullets;
    bool lost = false;
    bool won = false;
    sf::Clock spawnClock;
    sf::Clock lifetimeClock;
};
