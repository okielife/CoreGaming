#include "../geometry.h"
#include "../game.h"
#include "BulletHell.h"

void SceneBulletHell::update(Game& game, float const dt)
{
    if (game.input.wasPressed(Action::Quit))
    {
        this->done = true;
        this->nextScene = SceneID::Title;
    }

    // Player movement
    if (Input::isDown(Action::MoveUp)) this->playerTransform.y -= playerSpeed * dt;
    if (Input::isDown(Action::MoveDown)) this->playerTransform.y += playerSpeed * dt;
    if (Input::isDown(Action::MoveLeft)) this->playerTransform.x -= playerSpeed * dt;;
    if (Input::isDown(Action::MoveRight)) this->playerTransform.x += playerSpeed * dt;

    // Keep player in action window
    this->playerTransform.x = std::clamp(this->playerTransform.x, actionWindowX, actionWindowX + actionWindowWidth - playerWidth);
    this->playerTransform.y = std::clamp(this->playerTransform.y, actionWindowY, actionWindowY + actionWindowHeight - playerHeight);

    if (!lost && !won)
    {
        // Spawn bullets for limited time
        if (lifetimeClock.getElapsedTime().asSeconds() < bulletSpawnDuration)
        {
            if (spawnClock.getElapsedTime().asSeconds() >= bulletSpawnInterval)
            {
                spawnClock.restart();
                Bullet b;
                b.transform.x = WINDOW_WIDTH + bulletWidth;
                b.transform.y =  bulletHeightDistribution(gen);
                b.speed = bulletSpeedDistribution(gen);
                this->bullets.push_back(b);
            }
        }

        // Move bullets
        for (auto& [transform, speed] : this->bullets)
        {
            transform.x -= speed * dt;
        }

        // Collision + cleanup
        const AABB playerBox = makeAABB(this->playerTransform, this->playerRect);
        std::erase_if(
            this->bullets,
            [&](const Bullet& b)
            {
                const AABB bulletBox = makeAABB(b.transform, this->bulletRect);
                if (intersects(bulletBox, playerBox))
                {
                    this->lost = true;
                    return false;
                }
                return bulletBox.x + bulletBox.w < 0.f;
            }
        );

        // Win condition
        if (this->lifetimeClock.getElapsedTime().asSeconds() >= bulletSpawnDuration && this->bullets.empty())
        {
            this->won = true;
        }
    }
}

void SceneBulletHell::render(Game& game, Renderer& renderer)
{
    renderer.begin(this->camera);
    renderer.drawUI(actionWindowRect, actionWindowTransform);
    renderer.drawUI(playerRect, playerTransform);
    if (won)
    {
        renderer.drawScreenText(25, 25, "You won!", sf::Color::Green);
    }
    else if (lost)
    {
        renderer.drawScreenText(25, 25, "You LOST!", sf::Color::Red);
    }
    for (const auto& bullet : bullets)
        renderer.drawUI(bulletRect, bullet.transform);
    renderer.end();
}
