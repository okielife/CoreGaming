#include "game.h"


Game::Game(Platform& platform) : platform_(platform), renderer_(platform.renderer()), input_(platform.input()) {
    camera_.w = 800;
    camera_.h = 600;
}

void Game::update(const float dt) {
    const auto& input = platform_.input();

    if (input.isDown(Action::MoveUp))    playerY_ -= speed_ * dt;
    if (input.isDown(Action::MoveDown))  playerY_ += speed_ * dt;
    if (input.isDown(Action::MoveLeft))  playerX_ -= speed_ * dt;
    if (input.isDown(Action::MoveRight)) playerX_ += speed_ * dt;

    camera_.x = playerX_ - static_cast<float>(camera_.w) / 2;
    camera_.y = playerY_ - static_cast<float>(camera_.h) / 2;
}

void Game::render()
{
    renderer_.begin();

    // Draw simple map (grid)
    for (int y = 0; y < 50; ++y) {
        for (int x = 0; x < 50; ++x) {
            renderer_.drawRect(
                static_cast<float>(x) * 32, static_cast<float>(y) * 32, 30, 30,
                camera_, {40, 40, 40, 255}
            );
        }
    }

    // Draw player
    renderer_.drawRect(
        playerX_, playerY_, 28, 28,
        camera_, {200, 80, 80, 255}
    );

    renderer_.end();
}
