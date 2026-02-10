#include <states/StatePlaying.hpp>

#include "game.hpp"

void StatePlaying::update(Game & game, float const dt)
{
    world.update(game, dt);
    if (auto const e = world.pollEvent(); e == WorldEvent::Exit) {
        pendingCommand = GameCommand::Exit;
    }
}

void StatePlaying::render(Game & game, Renderer & renderer)
{
    world.render(game, renderer);
}
