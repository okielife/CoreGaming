#include "../game.h"
#include "BulletHell.h"

SceneBulletHell::SceneBulletHell()
{
    player = sf::RectangleShape({25.f, 25.f});
    player.setFillColor(sf::Color::Blue);
    player.setPosition(100.f, 200.f);
}

void SceneBulletHell::update(Game& game, float const dt)
{
    float localDT = frameClock.restart().asSeconds();
    if (!lost && !won) {
        // Player movement
        sf::Vector2f move{0.f, 0.f};
        if (Input::isDown(Action::MoveUp))    move.y -= playerSpeed * dt;
        if (Input::isDown(Action::MoveDown))  move.y += playerSpeed * dt;
        if (Input::isDown(Action::MoveLeft))  move.x -= playerSpeed * localDT;;
        if (Input::isDown(Action::MoveRight)) move.x += playerSpeed * dt;
        player.move(move);

        // Keep player on screen
        sf::Vector2f pos = player.getPosition();
        pos.x = std::clamp(pos.x, 0.f, 800.f - player.getSize().x);
        pos.y = std::clamp(pos.y, 0.f, 450.f - player.getSize().y);
        player.setPosition(pos);

        // Spawn bullets for limited time
        if (lifetimeClock.getElapsedTime().asSeconds() < bulletSpawnDuration) {
            if (spawnClock.getElapsedTime().asSeconds() >= bulletSpawnInterval) {
                spawnClock.restart();

                Bullet b;
                b.shape.setSize({12.f, 6.f});
                b.shape.setFillColor(sf::Color::Red);
                b.shape.setPosition(
                    800.f,
                    static_cast<float>(std::rand() % (450 - 10))
                );
                b.speed = bulletSpeedMin +
                          static_cast<float>(std::rand()) / RAND_MAX *
                              (bulletSpeedMax - bulletSpeedMin);

                bullets.push_back(b);
            }
        }

        // Move bullets
        for (auto& b : bullets) {
            b.shape.move(-b.speed * dt, 0.f);
        }

        // Collision + cleanup
        bullets.erase(
            std::remove_if(bullets.begin(), bullets.end(),
                [&](Bullet& b) {
                    if (b.shape.getGlobalBounds().intersects(
                            player.getGlobalBounds())) {
                        lost = true;
                        return false;
                    }
                    return b.shape.getPosition().x + b.shape.getSize().x < 0.f;
                }),
            bullets.end()
        );

        // Win condition
        if (lifetimeClock.getElapsedTime().asSeconds() >= bulletSpawnDuration &&
            bullets.empty()) {
            won = true;
        }
    }
}

void SceneBulletHell::render(Game& game, Renderer& renderer)
{
    renderer.drawScreenSFRectangle(player);
    if (won)
    {
        renderer.drawScreenText(25, 25, "You won!", sf::Color::Green);
    } else if (lost)
    {
        renderer.drawScreenText(25, 25, "You LOST!", sf::Color::Red);
    }
    for (const auto & [shape, _] : bullets)
        renderer.drawScreenSFRectangle(shape);
}
