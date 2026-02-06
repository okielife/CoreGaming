#pragma once

#include <random>

#include <scenes/base.h>

struct Bullet {
    Transform transform;
    float speed = 0.0;
};

class SceneBulletHell : public SceneBase {
public:
    SceneBulletHell()
    {
        std::random_device rd;
        this->gen = std::mt19937(rd());
        this->bulletHeightDistribution = std::uniform_int_distribution(0, WINDOW_HEIGHT);
        this->bulletSpeedDistribution = std::uniform_int_distribution(200, 400);
    }
    void update(Game & game, float dt) override;
    void render(Game & game, Renderer &renderer) override;
private:
    Rect playerRect {.w = 25.0, .h = 25.0, .color = sf::Color::Blue};
    Transform playerTransform {
        .x = WINDOW_WIDTH / 2.0f - playerRect.w / 2.0f,
        .y = WINDOW_HEIGHT / 2.0f - playerRect.h / 2.0f
    };
    Rect actionWindowRect {
        .w = 400,
        .h = 400,
        .color = sf::Color::Transparent,
        .outlineColor = sf::Color::Yellow,
        .outlineThickness = 1.0,
    };
    Transform actionWindowPosition {
        .x = WINDOW_WIDTH / 2.0f - actionWindowRect.w / 2.0f,
        .y = WINDOW_HEIGHT / 2.0f - actionWindowRect.h / 2.0f,
    };
    Rect bulletRect { // shared among all bullets for now
        .w = 10.0,
        .h = 5.0,
        .color = sf::Color::Red
    };
    Text outcome {.fontID = FontID::UbuntuRegular, .fontSize = 24};
    static constexpr Transform outcomeTransform {.x = 25, .y = 25};
    std::vector<Bullet> bullets;
    bool lost = false;
    bool won = false;
    sf::Clock spawnClock;
    sf::Clock lifetimeClock;
    std::mt19937 gen;
    std::uniform_int_distribution<> bulletHeightDistribution;
    std::uniform_int_distribution<> bulletSpeedDistribution;
};
