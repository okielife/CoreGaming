#include <game.hpp>
#include <scenes/RoomGridShow.hpp>

void RoomGridShow::update(Game & game, const float dt)
{
    // update timers
    msSinceLastSword += dt;

    const auto& input = game.input;
    if (input.wasPressed(Action::Quit))
    {
        status = RoomStatus::Complete;
        return;
    }

    constexpr float speed = 200;
    if (Input::isDown(Action::MoveUp)) playerTransform.y -= speed * dt;
    if (Input::isDown(Action::MoveDown)) playerTransform.y += speed * dt;
    if (Input::isDown(Action::MoveLeft))playerTransform.x -= speed * dt;
    if (Input::isDown(Action::MoveRight)) playerTransform.x += speed * dt;
    if (Input::isDown(Action::ZoomIn)) camera.zoom *= 1.01;
    if (Input::isDown(Action::ZoomOut)) camera.zoom /= 1.01;

    if (input.wasPressed(Action::Enter))
    {
        if (msSinceLastSword >= swordCooldownMS)
        {
            game.audio.playSound("sword.wav");
            msSinceLastSword = 0.0f;
        }
    }

    camera.x = playerTransform.x; // - static_cast<float>(camera.w) / 2;
    camera.y = playerTransform.y; // - static_cast<float>(camera.h) / 2;
}

void RoomGridShow::render(Game &, Renderer & renderer)
{
    renderer.begin(camera);

    // Draw simple map (grid)
    for (int y = 0; y < 50; ++y) {
        for (int x = 0; x < 50; ++x) {
            mapGridTransform.x = static_cast<float>(x) * 32;
            mapGridTransform.y = static_cast<float>(y) * 32;
            renderer.draw(mapGridRect, mapGridTransform);
        }
    }

    // Draw player
    renderer.draw(playerRect, playerTransform);

    // Draw some text
    renderer.drawUI(instructions, instructionsTransform);
    coordinates.text = "Player X, Y = " + std::to_string(playerTransform.x) + ", " + std::to_string(playerTransform.y);
    renderer.drawUI(coordinates, coordinatesTransform);
    renderer.end();
}