#include <collision.hpp>
#include <game.hpp>
#include <rooms/RoomBulletHell.hpp>

void RoomBulletHell::update(Game& game, float const dt)
{
    if (game.input.pressedThisFrame(Action::Quit))
    {
        if (won)
        {
            status = RoomStatus::Complete;
        }
        else if (lost)
        {
            status = RoomStatus::Failed;
        }
        else
        {
            status = RoomStatus::Incomplete;
        }
        return;
    }

    if (lost)
    {
        if (game.input.pressedThisFrame(Action::Confirm)) resetAfterFailure();
    }

    // Player movement
    constexpr float playerSpeed = 300.f;
    playerTransform.x += game.input.axisCurrentValue(Axis::X) * playerSpeed * dt;
    playerTransform.y += game.input.axisCurrentValue(Axis::Y) * playerSpeed * dt;

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
        constexpr float bulletSpawnDuration = 4.0f;
        lifetime += dt;
        if (lifetime < bulletSpawnDuration)
        {
            spawnAccumulator += dt;
            if (spawnAccumulator >= bulletSpawnInterval)
            {
                spawnAccumulator -= bulletSpawnInterval;
                Bullet b;
                b.transform.x = WINDOW_WIDTH + bulletRect.w;
                b.transform.y = static_cast<float>(bulletHeightDistribution(gen));
                b.speed = static_cast<float>(bulletSpeedDistribution(gen));
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
        if (lifetime >= bulletSpawnDuration && bullets.empty())
        {
            won = true;
        }
    }
}

void RoomBulletHell::render(Game& game, Renderer& renderer)
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
        outcome.text = "Lost: ESC to exit or STAY DETERMINED and press ENTER to restart!";
        outcome.color = sf::Color::Red;
        renderer.drawUI(outcome, outcomeTransform);
    }
    for (const auto& [transform, _] : bullets)
        renderer.draw(bulletRect, transform);
    renderer.end();
}

void RoomBulletHell::reset()
{
    won = false;
    lost = false;
    status = RoomStatus::None;
    nextRoomID = RoomID::None;
}