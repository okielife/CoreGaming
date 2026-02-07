#pragma once

#include <memory>

#include <command.hpp>
#include <scenes/RoomBase.hpp>

class Game;

class World {
public:
    World();
    void update(Game & game, float dt);
    void changeRoom(Game & game, RoomID room);
    void render(Game & game, Renderer & renderer);
    WorldEvent pollEvent();
private:
    std::unique_ptr<RoomBase> currentRoom;
    WorldEvent pendingEvent = WorldEvent::None;
};
