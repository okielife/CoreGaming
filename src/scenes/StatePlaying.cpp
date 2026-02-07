#include <scenes/StatePlaying.hpp>

#include "game.hpp"
// #include "input.hpp"

void StatePlaying::update(Game & game, float const dt)
{
    // // How does input and time affect the game right now?
    // if (game.input.wasPressed(Action::Quit))
    // {
    //     pendingCommand = GameCommand::Exit;
    //     return;
    // }
    world.update(game, dt);
    if (auto const e = world.pollEvent(); e == WorldEvent::Exit) {
        pendingCommand = GameCommand::Exit;
    }

    // if (input.pausePressed())
    // {
    //     pendingCommand = GameCommand::PushPause;
    // }
}

void StatePlaying::render(Game & game, Renderer & renderer)
{
    world.render(game, renderer);
}
