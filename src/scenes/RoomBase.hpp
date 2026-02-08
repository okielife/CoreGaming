#pragma once

#include <command.hpp>

class Game;
class Renderer;

enum class RoomStatus
{
    None,
    Complete,
    Incomplete,
    Failed,
    // RoomChangeOnly,
    ExitGame
};

// TODO: Maybe RoomBase should have a bool allowReentry so that it won't re-init things
class RoomBase {
public:
    virtual ~RoomBase() = default;
    virtual void update(Game & game, float dt) = 0;
    virtual void render(Game & game, Renderer & renderer) = 0;
    virtual void reset() {}
    RoomStatus status = RoomStatus::None;
    RoomID nextRoomID = RoomID::None;
};
