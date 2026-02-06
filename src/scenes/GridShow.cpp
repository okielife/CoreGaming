#include <game.h>
#include <scenes/GridShow.h>

void SceneGridShow::update(Game & game, const float dt)
{
    // update timers
    this->msSinceLastSword += dt;

    const auto& input = game.input;
    if (input.wasPressed(Action::Quit))
    {
        this->done = true;
        this->nextScene = SceneID::Title;
    }

    constexpr float speed = 200;
    if (Input::isDown(Action::MoveUp)) this->playerTransform.y -= speed * dt;
    if (Input::isDown(Action::MoveDown)) this->playerTransform.y += speed * dt;
    if (Input::isDown(Action::MoveLeft))this->playerTransform.x -= speed * dt;
    if (Input::isDown(Action::MoveRight)) this->playerTransform.x += speed * dt;
    if (Input::isDown(Action::ZoomIn)) this->camera.zoom *= 1.01;
    if (Input::isDown(Action::ZoomOut)) this->camera.zoom /= 1.01;

    if (input.wasPressed(Action::Enter))
    {
        if (msSinceLastSword >= swordCooldownMS)
        {
            game.audio.playSound(SoundID::Sword);
            msSinceLastSword = 0.0f;
        }
    }

    this->camera.x = this->playerTransform.x; // - static_cast<float>(this->camera.w) / 2;
    this->camera.y = this->playerTransform.y; // - static_cast<float>(this->camera.h) / 2;
}

void SceneGridShow::render(Game &, Renderer & renderer)
{
    renderer.begin(this->camera);

    // Draw simple map (grid)
    for (int y = 0; y < 50; ++y) {
        for (int x = 0; x < 50; ++x) {
            this->mapGridTransform.x = static_cast<float>(x) * 32;
            this->mapGridTransform.y = static_cast<float>(y) * 32;
            renderer.draw(mapGridRect, mapGridTransform);
        }
    }

    // Draw player
    renderer.draw(playerRect, playerTransform);

    // Draw some text
    renderer.setUIView();
    renderer.drawScreenText(20, 50, "Use Arrow Keys", sf::Color::Red);
    std::string const coordsString = "Player X, Y = " + std::to_string(this->playerTransform.x) + ", " + std::to_string(this->playerTransform.y);
    renderer.drawScreenText(200, 70, coordsString.c_str(), sf::Color::Red);
    renderer.end();
}