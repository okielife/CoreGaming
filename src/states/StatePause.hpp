#pragma once

#include <scenes/StatePlaying.hpp>
#include <game.hpp>
// #include <renderer.hpp>

class PauseState: public StatePlaying
{
    void update(float) {
        //if (Input::wasPressed(resume)) {
        //    pendingCommand = GameCommand::PopState;
        //}
    }

    void render(Game & game, Renderer & renderer)
    {
        // draw the pause state
    }
};
