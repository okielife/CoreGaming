#pragma once

#include <command.hpp>

class Game;
class Renderer;

class RoomBase {
public:
    virtual ~RoomBase() = default;
    virtual void update(Game & game, float dt) = 0;
    virtual void render(Game & game, Renderer & renderer) = 0;
    [[nodiscard]] RoomOutcome pollOutcome() const { return roomOutcome; }
    [[nodiscard]] RoomID pollExit() const { return nextRoomID; }
protected:
    RoomOutcome roomOutcome = RoomOutcome::None;
    RoomID nextRoomID = RoomID::None;
};
