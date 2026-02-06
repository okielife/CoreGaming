#include <game.h>
#include <scenes/Platformer.h>

void ScenePlatformer::update(Game & game, const float dt)
{
    const auto& input = game.input;
    if (input.wasPressed(Action::Quit))
    {
        this->done = true;
        this->nextScene = SceneID::Title;
    }

    // move
    if (input.isDown(Action::MoveLeft)) playerTransform.x -= 4.5;
    if (input.isDown(Action::MoveRight)) playerTransform.x += 4.5;

    // Jump
    if (input.wasPressed(Action::Enter) && grounded) {
        velocityY = -jumpSpeed;
        grounded = false;
    }

    // Gravity
    velocityY += gravity * dt;
    playerTransform.y += velocityY * dt;
    grounded = false;

    if (playerTransform.y > 4000) *this = ScenePlatformer(); // probably bad :|

    // Platform collision (top-only)
    const AABB playerBox = makeAABB(this->playerTransform, this->player);

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

    this->camera.x = this->playerTransform.x;
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
    // // Draw player
    // renderer.drawWorldSprite(
    //     SpriteDraw(
    //             SpriteID::Wizard,
    //             player.getSize().x, player.getSize().y,
    //             player.getPosition().x, player.getPosition().y,
    //             0.15, 0.15, 0, sf::Color::White
    //         ),
    //         this->camera
    //     );
    renderer.setUIView();
    if (won)
    {
        renderer.drawScreenText(20, 50, "WINNER!", sf::Color::Green);
    } else
    {
        renderer.drawScreenText(20, 50, "Use Arrow Keys and Space to Jump", sf::Color::Red);
    }
    renderer.end();
}