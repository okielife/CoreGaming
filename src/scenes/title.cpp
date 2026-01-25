#include "../assets.h"
#include "../game.h"
#include "title.h"
#include "../constants.h"

SceneTitle::SceneTitle(const Game &game)
{
    this->titleBackground_ = game.renderer->loadTexture(AssetManager::image("sky.png")); // move this out of constructor and into titleInitialize or something
}

void SceneTitle::reset([[maybe_unused]] Game & game)
{

}

void SceneTitle::reenter([[maybe_unused]] Game & game)
{

}

void SceneTitle::update(Game & game, const float)
{
    if (game.input.anyPressed()) {
        this->done = true;
    }
}

void SceneTitle::render(Game & game)
{
    game.renderer->begin();

    game.renderer->drawScreenTexture(
        titleBackground_,
        0, 0,
        WINDOW_WIDTH, WINDOW_HEIGHT
    );

    game.renderer->drawScreenText(
        10.f,
        10.f,
        "Press any key",
        RED
    );

    Renderer::end();
}