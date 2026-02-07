#include <geometry.h>
#include <game.h>
#include <scenes/BulletHell.h>

void SceneBulletHell::update(Game& game, float const dt)
{
    if (game.input.wasPressed(Action::Quit))
    {
        done = true;
        nextScene = SceneID::Title;
    }

    // Player movement
    constexpr float playerSpeed = 300.f;
    if (Input::isDown(Action::MoveUp)) playerTransform.y -= playerSpeed * dt;
    if (Input::isDown(Action::MoveDown)) playerTransform.y += playerSpeed * dt;
    if (Input::isDown(Action::MoveLeft)) playerTransform.x -= playerSpeed * dt;;
    if (Input::isDown(Action::MoveRight)) playerTransform.x += playerSpeed * dt;

    // Keep player in action window
    playerTransform.x = std::clamp(
        playerTransform.x, actionWindowPosition.x, actionWindowPosition.x + actionWindowRect.w - playerRect.w
        );
    playerTransform.y = std::clamp(
        playerTransform.y, actionWindowPosition.y, actionWindowPosition.y + actionWindowRect.h - playerRect.h
        );

    if (!lost && !won)
    {
        // Spawn bullets for limited time
        constexpr float bulletSpawnInterval = 0.05f;
        constexpr float bulletSpawnDuration = 4.f;
        if (lifetimeClock.getElapsedTime().asSeconds() < bulletSpawnDuration)
        {
            if (spawnClock.getElapsedTime().asSeconds() >= bulletSpawnInterval)
            {
                spawnClock.restart();
                Bullet b;
                b.transform.x = WINDOW_WIDTH + bulletRect.w;
                b.transform.y =  bulletHeightDistribution(gen);
                b.speed = bulletSpeedDistribution(gen);
                bullets.push_back(b);
            }
        }

        // Move bullets
        for (auto& [transform, speed] : bullets)
        {
            transform.x -= speed * dt;
        }

        // Collision + cleanup
        const AABB playerBox = makeAABB(playerTransform, playerRect);
        std::erase_if(
            bullets,
            [&](const Bullet& b)
            {
                const AABB bulletBox = makeAABB(b.transform, bulletRect);
                if (intersects(bulletBox, playerBox))
                {
                    lost = true;
                    return false;
                }
                return bulletBox.x + bulletBox.w < 0.f;
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
    renderer.begin(fixedDefaultCamera);
    renderer.draw(actionWindowRect, actionWindowPosition);
    renderer.draw(playerRect, playerTransform);
    if (won)
    {
        outcome.text = "You won!";
        outcome.color = sf::Color::Green;
        renderer.drawUI(outcome, outcomeTransform);
    }
    else if (lost)
    {
        outcome.text = "You lost!";
        outcome.color = sf::Color::Red;
        renderer.drawUI(outcome, outcomeTransform);
    }
    for (const auto& [transform, _] : bullets)
        renderer.draw(bulletRect, transform);
    renderer.end();
}
