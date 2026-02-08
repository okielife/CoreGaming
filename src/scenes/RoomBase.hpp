#pragma once

#include <command.hpp>

class Game;
class Renderer;

enum class RoomStatus
{
    None,
    Complete,
    Incomplete,
    Failed
};

class RoomBase {
public:
    virtual ~RoomBase() = default;
    virtual void update(Game & game, float dt) = 0;
    virtual void render(Game & game, Renderer & renderer) = 0;
    RoomStatus status = RoomStatus::None;
    RoomID nextRoomID = RoomID::None;
    // TODO: Need a re-enter method that will clear the status and next Room ID and such
    [[nodiscard]] bool leaveThisRoom() const { return status != RoomStatus::None; }
};
