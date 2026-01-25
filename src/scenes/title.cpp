#include "title.h"
#include "../game.h"
#include "../constants.h"

SceneTitle::SceneTitle(const Game &) {}

void SceneTitle::reset(Game &) {}

void SceneTitle::reenter(Game &) {}

void SceneTitle::update(Game & game, const float)
{
    if (game.input.anyPressed()) {
        this->done = true;
    }
}

void SceneTitle::render(Game &, Renderer & renderer)
{
    renderer.drawScreenTexture(
        TextureID::Sky,
        0, 0,
        WINDOW_WIDTH, WINDOW_HEIGHT
    );

    renderer.drawScreenText(
        10.f,
        10.f,
        "Press any key",
        sf::Color::Red
    );
}