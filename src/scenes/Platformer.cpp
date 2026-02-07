#include <game.hpp>
#include <collision.hpp>
#include <scenes/Platformer.hpp>

void ScenePlatformer::update(Game & game, const float dt)
{
    const auto& input = game.input;
    if (input.wasPressed(Action::Quit))
    {
        done = true;
        nextScene = SceneID::Title;
    }

    // move
    if (input.isDown(Action::MoveLeft)) playerTransform.x -= 4.5;
    if (input.isDown(Action::MoveRight)) playerTransform.x += 4.5;

    // Jump
    if (input.wasPressed(Action::Enter) && grounded) {
        constexpr float jumpSpeed = 650.f;
        velocityY = -jumpSpeed;
        grounded = false;
    }

    // Gravity
    constexpr float gravity = 1800.f;
    velocityY += gravity * dt;
    playerTransform.y += velocityY * dt;
    grounded = false;

    if (playerTransform.y > 4000) *this = ScenePlatformer(); // probably bad :|

    // Platform collision (top-only)
    const AABB playerBox = makeAABB(playerTransform, player);

    auto checkPlatform = [&](const Rect& platform, const Transform & platformTransform, bool const isGoal) {
        const AABB platformBox {.x = platformTransform.x, .y = platformTransform.y, .w = platform.w, .h = 1};
        if (intersects(platformBox, playerBox)) {
            float const playerBottom = playerTransform.y + player.h;
            float const platformTop = platformTransform.y;

            // Only land if falling and above platform
            if (velocityY > 0.f && playerBottom <= platformTop + 15.f) {
                playerTransform.y = platformTop - player.h;
                velocityY = 0.f;
                grounded = true;

                if (isGoal && !won) {
                    won = true;
                }
            }
        }
    };

    checkPlatform(platform1, platform1Transform, false);
    checkPlatform(platform2, platform2Transform, false);
    checkPlatform(platform3, platform3Transform, false);
    checkPlatform(goalPlatform, goalPlatformTransform, true);

    camera.x = playerTransform.x;
}

void ScenePlatformer::render(Game &, Renderer & renderer)
{
    renderer.begin(camera);
    // Draw platforms
    renderer.draw(platform1, platform1Transform);
    renderer.draw(platform2, platform2Transform);
    renderer.draw(platform3, platform3Transform);
    renderer.draw(goalPlatform, goalPlatformTransform);
    renderer.draw(player, playerTransform);
    if (won)
    {
        message.text = "WINNER!";
        message.color = sf::Color::Green;
        renderer.drawUI(message, messageTransform);
    } else
    {
        message.text = "Use Arrow Keys and Space to Jump";
        message.color = sf::Color::Blue;
        renderer.drawUI(message, messageTransform);
    }
    renderer.end();
}