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
    void clearPoll() {nextRoomID = RoomID::None;}
    [[nodiscard]] RoomID pollExit() const { return nextRoomID; }
    [[nodiscard]] bool isDone() const { return roomComplete;}
protected:
    RoomOutcome roomOutcome = RoomOutcome::None;
    RoomID nextRoomID = RoomID::None;
    void markDone() {roomComplete = true;}
private:
    bool roomComplete = false;
};
