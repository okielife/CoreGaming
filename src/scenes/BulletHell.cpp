#include "../game.h"
#include "BulletHell.h"

SceneBulletHell::SceneBulletHell()
{
    this->actionWindow = sf::RectangleShape({actionWindowWidth, actionWindowHeight});
    this->actionWindow.setFillColor(sf::Color::Transparent);
    this->actionWindow.setOutlineColor(sf::Color::Yellow);
    this->actionWindow.setOutlineThickness(1.f);
    this->actionWindow.setPosition(actionWindowX, actionWindowY);
    this->player = sf::RectangleShape({playerWidth, playerHeight});
    this->player.setFillColor(sf::Color::Blue);
    this->player.setPosition(WINDOW_WIDTH / 2.0 - playerWidth / 2.0, WINDOW_HEIGHT / 2.0 - playerHeight / 2.0);
}

void SceneBulletHell::update(Game& game, float const dt)
{
    const auto& input = game.input;
    if (input.wasPressed(Action::Quit))
    {
        this->done = true;
        this->nextScene = SceneID::Title;
    }

    // Player movement
    sf::Vector2f move{0.f, 0.f};
    if (Input::isDown(Action::MoveUp)) move.y -= playerSpeed * dt;
    if (Input::isDown(Action::MoveDown)) move.y += playerSpeed * dt;
    if (Input::isDown(Action::MoveLeft)) move.x -= playerSpeed * dt;;
    if (Input::isDown(Action::MoveRight)) move.x += playerSpeed * dt;
    player.move(move);

    // Keep player in action window
    sf::Vector2f pos = player.getPosition();
    pos.x = std::clamp(pos.x, actionWindowX, actionWindowX + actionWindowWidth - playerWidth);
    pos.y = std::clamp(pos.y, actionWindowY, actionWindowY + actionWindowHeight - playerHeight);
    player.setPosition(pos);

    if (!lost && !won)
    {
        // Spawn bullets for limited time
        if (lifetimeClock.getElapsedTime().asSeconds() < bulletSpawnDuration)
        {
            if (spawnClock.getElapsedTime().asSeconds() >= bulletSpawnInterval)
            {
                spawnClock.restart();
                Bullet b;
                b.shape.setSize({bulletWidth, bulletHeight});
                b.shape.setFillColor(sf::Color::Red);
                b.shape.setPosition(WINDOW_WIDTH + bulletWidth, static_cast<float>(std::rand() % WINDOW_HEIGHT));
                b.speed = bulletSpeedMin + static_cast<float>(std::rand()) / RAND_MAX * (bulletSpeedMax -
                    bulletSpeedMin);
                bullets.push_back(b);
            }
        }

        // Move bullets
        for (auto& [shape, speed] : bullets)
        {
            shape.move(-speed * dt, 0.f);
        }

        // Collision + cleanup
        std::erase_if(
            bullets,
            [&](const Bullet& b)
            {
                if (b.shape.getGlobalBounds().intersects(player.getGlobalBounds()))
                {
                    lost = true;
                    return false;
                }
                return b.shape.getPosition().x + b.shape.getSize().x < 0.f;
            }
        );

        // Win condition
        if (lifetimeClock.getElapsedTime().asSeconds() >= bulletSpawnDuration && bullets.empty())
        {
            won = true;
        }
    }
}

void SceneBulletHell::render(Game& game, Renderer& renderer)
{
    renderer.drawScreenSFRectangle(this->actionWindow);
    renderer.drawScreenSFRectangle(player);
    if (won)
    {
        renderer.drawScreenText(25, 25, "You won!", sf::Color::Green);
    }
    else if (lost)
    {
        renderer.drawScreenText(25, 25, "You LOST!", sf::Color::Red);
    }
    for (const auto& [shape, _] : bullets)
        renderer.drawScreenSFRectangle(shape);
}
