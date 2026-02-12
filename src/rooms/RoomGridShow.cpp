#include <game.hpp>
#include <rooms/RoomGridShow.hpp>

void RoomGridShow::update(Game & game, const float dt)
{
    // update timers
    msSinceLastSword += dt;

    const auto& input = game.input;
    if (input.pressedThisFrame(Action::Quit))
    {
        status = RoomStatus::Complete;
        return;
    }

    constexpr float speed = 200;
    playerTransform.x += game.input.axisCurrentValue(Axis::X) * speed * dt;
    playerTransform.y += game.input.axisCurrentValue(Axis::Y) * speed * dt;
    camera.zoom += game.input.axisCurrentValue(Axis::Zoom) * 1.01f;

    if (input.pressedThisFrame(Action::Space))
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