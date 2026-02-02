#include "../game.h"
#include "Platformer.h"

class Game;

ScenePlatformer::ScenePlatformer()
{
    // Player
    player = sf::RectangleShape({30.f, 40.f});
    player.setFillColor(sf::Color::Blue);
    player.setPosition(100.f, 250.f);
    // Platforms
    startPlatform = sf::RectangleShape({200.f, 20.f});
    startPlatform.setFillColor(sf::Color(120, 120, 120));
    startPlatform.setPosition(50.f, 300.f);
    goalPlatform = sf::RectangleShape({200.f, 20.f});
    goalPlatform.setFillColor(sf::Color::Green);
    goalPlatform.setPosition(400.f, 230.f);
}

void ScenePlatformer::reset(Game &) {}

void ScenePlatformer::reenter(Game &) {}

void ScenePlatformer::update(Game & game, const float dt)
{
    const auto& input = game.input;
    if (input.wasPressed(Action::Quit))
    {
        this->done = true;
        this->nextScene = SceneID::Exit;
    }

    // move
    if (input.isDown(Action::MoveLeft)) player.move(-4.5, 0.0);
    if (input.isDown(Action::MoveRight)) player.move(4.5, 0.0);

    // Jump
    if (input.wasPressed(Action::Sword) && grounded) {
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

    checkPlatform(startPlatform, false);
    checkPlatform(goalPlatform, true);
}

void ScenePlatformer::render(Game &, Renderer & renderer)
{
    // Draw platforms
    renderer.drawScreenRectangleOutline(startPlatform.getPosition().x, startPlatform.getPosition().y, startPlatform.getSize().x, startPlatform.getSize().y, sf::Color(120, 120, 120));;
    renderer.drawScreenRectangleOutline(goalPlatform.getPosition().x, goalPlatform.getPosition().y, goalPlatform.getSize().x, goalPlatform.getSize().y, sf::Color::Green);;
    // Draw player
    renderer.drawSprite(SpriteDraw(SpriteID::Wizard, player.getSize().x, player.getSize().y, player.getPosition().x, player.getPosition().y, 0.15, 0.15, 0, sf::Color::White));
    if (won)
    {
        renderer.drawScreenText(20, 50, "WINNER!", sf::Color::Green);
    } else
    {
        renderer.drawScreenText(20, 50, "Use WASD", sf::Color::Red);
        //std::string const coordsString = "Player X, Y = " + std::to_string(this->playerPos.x) + ", " + std::to_string(this->playerPos.y);
        //renderer.drawScreenText(200, 70, coordsString.c_str(), sf::Color::Red);
    }
}