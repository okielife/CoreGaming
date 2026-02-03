#include <array>

#include "../game.h"
#include "Platformer.h"

class Game;

ScenePlatformer::ScenePlatformer()
{
    // Player
    player = sf::RectangleShape({30.f, 40.f});
    player.setFillColor(sf::Color::Blue);
    player.setPosition(100.f, 150.f);
    // Platforms
    auto const normalPlatformColor = sf::Color(120, 120, 120);
    constexpr std::array platformData = {
        PlatformData{200.0f, 20.0f, 50.0f, 300.0f},
        PlatformData{200.0f, 20.0f, 400.0f, 230.0f},
        PlatformData{150.0f, 20.0f, 850.0f, 380.0f},
    };
    for (auto const & [width, height, x_left, y_top] : platformData)
    {
        auto thisPlatform = sf::RectangleShape({width, height});
        thisPlatform.setFillColor(normalPlatformColor);
        thisPlatform.setPosition(x_left, y_top);
        this->platforms.push_back(thisPlatform);
    }
    goalPlatform = sf::RectangleShape({100.f, 2.f});
    goalPlatform.setFillColor(sf::Color::Green);
    goalPlatform.setPosition(1160.f, 320.f);
    // Camera
    this->camera.y = 0;
}

void ScenePlatformer::reset(Game &) {}

void ScenePlatformer::reenter(Game &) {}

void ScenePlatformer::update(Game & game, const float dt)
{
    const auto& input = game.input;
    if (input.wasPressed(Action::Quit))
    {
        this->done = true;
        this->nextScene = SceneID::Title;
    }

    // move
    if (input.isDown(Action::MoveLeft)) player.move(-4.5, 0.0);
    if (input.isDown(Action::MoveRight)) player.move(4.5, 0.0);

    // Jump
    if (input.wasPressed(Action::Enter) && grounded) {
        velocityY = -jumpSpeed;
        grounded = false;
    }

    // Gravity
    velocityY += gravity * dt;
    player.move(0.f, velocityY * dt);
    grounded = false;

    if (player.getPosition().y > 4000) *this = ScenePlatformer(); // probably bad :|

    // Platform collision (top-only)
    auto checkPlatform = [&](const sf::RectangleShape& platform, bool const isGoal) {
        if (player.getGlobalBounds().intersects(platform.getGlobalBounds())) {
            float const playerBottom = player.getPosition().y + player.getSize().y;
            float const platformTop = platform.getPosition().y;

            // Only land if falling and above platform
            if (velocityY > 0.f && playerBottom <= platformTop + 15.f) {
                player.setPosition(
                    player.getPosition().x,
                    platformTop - player.getSize().y
                );
                velocityY = 0.f;
                grounded = true;

                if (isGoal && !won) {
                    won = true;
                }
            }
        }
    };

    for (auto & platform : platforms)
    {
        checkPlatform(platform, false);
    }
    checkPlatform(goalPlatform, true);

    this->camera.x = this->player.getPosition().x - static_cast<float>(this->camera.w) / 2;
    // this->overheadCamera.y = this->player.getPosition().y - static_cast<float>(this->overheadCamera.h) / 2;
}

void ScenePlatformer::render(Game &, Renderer & renderer)
{
    // Draw platforms
    for (auto & platform : platforms)
    {
        renderer.drawWorldRectangleOutline(platform.getPosition().x, platform.getPosition().y, platform.getSize().x, platform.getSize().y, camera, sf::Color(120, 120, 120));
    }

    renderer.drawWorldRectangleOutline(goalPlatform.getPosition().x, goalPlatform.getPosition().y, goalPlatform.getSize().x, goalPlatform.getSize().y, camera, sf::Color::Green);;
    // Draw player
    renderer.drawWorldSprite(
        SpriteDraw(
                SpriteID::Wizard,
                player.getSize().x, player.getSize().y,
                player.getPosition().x, player.getPosition().y,
                0.15, 0.15, 0, sf::Color::White
            ),
            this->camera
        );
    if (won)
    {
        renderer.drawScreenText(20, 50, "WINNER!", sf::Color::Green);
    } else
    {
        renderer.drawScreenText(20, 50, "Use Arrow Keys and Space to Jump", sf::Color::Red);
        //std::string const coordsString = "Player X, Y = " + std::to_string(this->playerPos.x) + ", " + std::to_string(this->playerPos.y);
        //renderer.drawScreenText(200, 70, coordsString.c_str(), sf::Color::Red);
    }
}