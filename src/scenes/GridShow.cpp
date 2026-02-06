#include <game.h>
#include <scenes/GridShow.h>

class Game;

void SceneGridShow::reset(Game &) {}

void SceneGridShow::reenter(Game &) {}

void SceneGridShow::update(Game & game, const float dt)
{
    // update timers
    msSinceLastSword += dt;

    const auto& input = game.input;
    if (input.wasPressed(Action::Quit))
    {
        this->done = true;
        this->nextScene = SceneID::Title;
    }

    if (Input::isDown(Action::MoveUp))    this->playerY_ -= this->speed_ * dt;
    if (Input::isDown(Action::MoveDown))  this->playerY_ += this->speed_ * dt;
    if (Input::isDown(Action::MoveLeft))  this->playerX_ -= this->speed_ * dt;
    if (Input::isDown(Action::MoveRight)) this->playerX_ += this->speed_ * dt;
    if (Input::isDown(Action::ZoomIn)) this->overheadCamera.zoom *= 1.01;
    if (Input::isDown(Action::ZoomOut)) this->overheadCamera.zoom /= 1.01;

    if (input.wasPressed(Action::Enter))
    {
        if (msSinceLastSword >= swordCooldownMS)
        {
            game.audio.playSound(SoundID::Sword);
            msSinceLastSword = 0.0f;
        }
    }

    this->overheadCamera.x = this->playerX_ - static_cast<float>(this->overheadCamera.w) / 2;
    this->overheadCamera.y = this->playerY_ - static_cast<float>(this->overheadCamera.h) / 2;
}

void SceneGridShow::render(Game &, Renderer & renderer)
{
    // Draw simple map (grid)
    for (int y = 0; y < 50; ++y) {
        for (int x = 0; x < 50; ++x) {
            renderer.drawWorldRectangleOutline(
                static_cast<float>(x) * 32, static_cast<float>(y) * 32, 30, 30,
                this->overheadCamera, {40, 40, 40, 255}
            );
        }
    }

    // Draw player
    renderer.drawWorldRectangleOutline(
        this->playerX_, this->playerY_, 28, 28,
        this->overheadCamera, {200, 80, 80, 255}
    );

    // Draw some text
    renderer.drawScreenText(20, 50, "Use Arrow Keys", sf::Color::Red);
    std::string const coordsString = "Player X, Y = " + std::to_string(this->playerX_) + ", " + std::to_string(this->playerY_);
    renderer.drawScreenText(200, 70, coordsString.c_str(), sf::Color::Red);
}