#include "../constants.h"
#include "../game.h"
#include "title.h"

class Game;

void SceneLevel1::reset([[maybe_unused]] Game & game)
{

}

void SceneLevel1::reenter([[maybe_unused]] Game & game)
{

}

void SceneLevel1::update(Game & game, const float dt)
{
    const auto& input = game.input;
    if (input.wasPressed(Action::Quit)) this->done = true;

    if (input.isDown(Action::MoveUp))    this->playerY_ -= this->speed_ * dt;
    if (input.isDown(Action::MoveDown))  this->playerY_ += this->speed_ * dt;
    if (input.isDown(Action::MoveLeft))  this->playerX_ -= this->speed_ * dt;
    if (input.isDown(Action::MoveRight)) this->playerX_ += this->speed_ * dt;
    if (input.isDown(Action::ZoomIn)) this->overheadCamera.zoom *= 1.01;
    if (input.isDown(Action::ZoomOut)) this->overheadCamera.zoom /= 1.01;

    this->overheadCamera.x = this->playerX_ - static_cast<float>(this->overheadCamera.w) / 2;
    this->overheadCamera.y = this->playerY_ - static_cast<float>(this->overheadCamera.h) / 2;
}

void SceneLevel1::render(Game & game)
{
    game.renderer.begin();

    // Draw simple map (grid)
    for (int y = 0; y < 50; ++y) {
        for (int x = 0; x < 50; ++x) {
            game.renderer.drawWorldRectangleOutline(
                static_cast<float>(x) * 32, static_cast<float>(y) * 32, 30, 30,
                this->overheadCamera, {40, 40, 40, 255}
            );
        }
    }

    // Draw player
    game.renderer.drawWorldRectangleOutline(
        this->playerX_, this->playerY_, 28, 28,
        this->overheadCamera, {200, 80, 80, 255}
    );

    // Draw some text
    game.renderer.drawScreenText(20, 50, "Use WASD", RED);
    std::string const coordsString = "Player X, Y = " + std::to_string(this->playerX_) + ", " + std::to_string(this->playerY_);
    game.renderer.drawScreenText(200, 70, coordsString.c_str(), RED);

    game.renderer.end();
}