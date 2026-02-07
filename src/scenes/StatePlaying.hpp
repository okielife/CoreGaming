#pragma once

#include <scenes/StateBase.hpp>
#include <scenes/World.hpp>

class Game;
class Renderer;

class StatePlaying : public GameState {
public:
    void update(Game & game, float dt) override;
    void render(Game & game, Renderer & renderer) override;

private:
    World world;
};
