#include <scenes/CutSceneWizardSpells.hpp>  // TODO: Remove this as a room
#include <scenes/RoomBulletHell.hpp>
#include <scenes/RoomGridShow.hpp>
#include <scenes/RoomHub.hpp>
#include <scenes/RoomMaze.hpp>
#include <scenes/RoomPlatformer.hpp>
#include "scenes/World.hpp"

World::World()
{
    rooms[RoomID::Hub] = std::make_unique<RoomHub>(*this);
    rooms[RoomID::BulletHell] = std::make_unique<RoomBulletHell>();
    rooms[RoomID::Maze] = std::make_unique<RoomMaze>();
    rooms[RoomID::GridShow] = std::make_unique<RoomGridShow>();
    rooms[RoomID::WizardSpells] = std::make_unique<RoomWizardSpells>();
    rooms[RoomID::Platformer] = std::make_unique<RoomPlatformer>();
    changeRoom(RoomID::Hub);
}

void World::update(Game & game, const float dt) {
    currentRoom->update(game, dt);
    if (currentRoom->nextRoomID == RoomID::ExitGame)
    {
        pendingEvent = WorldEvent::Exit;
        return;
    }
    if (currentRoom->status == RoomStatus::None && currentRoom->nextRoomID == RoomID::None)
    {
        return; // nothing to do
    }
    // at this point, either next room has been set or a completion status update occurred, change rooms
    RoomID const nextRoomID = currentRoom->nextRoomID != RoomID::None ? currentRoom->nextRoomID : RoomID::Hub;
    currentRoom->nextRoomID = RoomID::None;
    changeRoom(nextRoomID);
}

void World::render(Game & game, Renderer & renderer) const
{
    currentRoom->render(game, renderer);
}

void World::changeRoom(RoomID const room)
{
    currentRoom = rooms.at(room).get();
}

WorldEvent World::pollEvent() {
    auto const e = pendingEvent;
    pendingEvent = WorldEvent::None;
    return e;
}
