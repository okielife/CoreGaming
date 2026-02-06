#pragma once

#include <random>

#include "base.h"

class Game;
class Renderer;

struct Bullet {
    Transform transform;
    float speed = 0.0;
};

constexpr float playerSpeed = 300.f;
constexpr float bulletWidth = 10.0f;
constexpr float bulletHeight = 5.0f;
constexpr int bulletSpeedMin = 200.f;
constexpr int bulletSpeedMax = 400.f;
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
    SceneBulletHell()
    {
        std::random_device rd;
        this->gen = std::mt19937(rd());
        this->bulletHeightDistribution = std::uniform_int_distribution(0, WINDOW_HEIGHT);
        this->bulletSpeedDistribution = std::uniform_int_distribution(bulletSpeedMin, bulletSpeedMax);
    }
    void reset(Game & game) override {};
    void reenter(Game & game) override {};
    void update(Game & game, float dt) override;
    void render(Game & game, Renderer &renderer) override;
private:
    Rect playerRect {
        .w = playerWidth,
        .h = playerHeight,
        .color = sf::Color::Blue
    };
    Transform playerTransform {
        .x = WINDOW_WIDTH / 2.0 - playerWidth / 2.0,
        .y = WINDOW_HEIGHT / 2.0 - playerHeight / 2.0
    };
    Rect actionWindowRect {
        .w = actionWindowWidth,
        .h = actionWindowHeight,
        .color = sf::Color::Transparent,
        .outlineColor = sf::Color::Yellow,
        .outlineThickness = 1.0,
    };
    Transform actionWindowTransform {
        .x = actionWindowX,
        .y = actionWindowY,
    };
    Rect bulletRect { // shared among all bullets for now
        .w = bulletWidth,
        .h = bulletHeight,
        .color = sf::Color::Red
    };
    std::vector<Bullet> bullets;
    bool lost = false;
    bool won = false;
    sf::Clock spawnClock;
    sf::Clock lifetimeClock;
    Camera camera;
    std::mt19937 gen;
    std::uniform_int_distribution<> bulletHeightDistribution;
    std::uniform_int_distribution<> bulletSpeedDistribution;
};
