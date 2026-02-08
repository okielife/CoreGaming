#pragma once

#include <memory>
#include <unordered_map>

#include <command.hpp>
#include <scenes/RoomBase.hpp>

class Game;

class World {
public:
    World();
    void update(Game & game, float dt);
    void changeRoom(RoomID room);
    void render(Game & game, Renderer & renderer) const;
    WorldEvent pollEvent();
    bool isRoomCompleted(RoomID const room) const
    {
        return rooms.at(room)->status == RoomStatus::Complete;
    }
private:
    RoomID currentRoomID = RoomID::None;
    RoomBase * currentRoom = nullptr;
    WorldEvent pendingEvent = WorldEvent::None;
    std::unordered_map<RoomID, std::unique_ptr<RoomBase>> rooms;
    std::unique_ptr<RoomBase> getNewRoomInstance(RoomID room);
};
