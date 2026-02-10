#include <scenes/CutSceneWizardSpells.hpp>  // TODO: Remove this as a room
#include <rooms/RoomBulletHell.hpp>
#include <rooms/RoomGridShow.hpp>
#include <rooms/RoomHub.hpp>
#include <rooms/RoomMaze.hpp>
#include <rooms/RoomPlatformer.hpp>
#include "worlds/World.hpp"

std::unique_ptr<RoomBase> World::getNewRoomInstance(RoomID const room)
{
    switch (room)
    {
    case RoomID::Hub: return std::make_unique<RoomHub>(*this);
    case RoomID::BulletHell: return std::make_unique<RoomBulletHell>();
    case RoomID::Maze: return std::make_unique<RoomMaze>();
    case RoomID::GridShow: return std::make_unique<RoomGridShow>();
    case RoomID::WizardSpells: return std::make_unique<RoomWizardSpells>();
    case RoomID::Platformer: return std::make_unique<RoomPlatformer>();
    default:
        throw std::runtime_error("Unknown Room ID");
    }
}

World::World()
{
    constexpr std::array roomsInWorld = {
        RoomID::Hub,
        RoomID::BulletHell,
        RoomID::Maze,
        RoomID::GridShow,
        RoomID::WizardSpells,
        RoomID::Platformer,
    };
    for (auto const & room : roomsInWorld) rooms[room] = getNewRoomInstance(room);
    changeRoom(RoomID::Hub);
}

void World::update(Game & game, const float dt) {

    // update the room, which will trigger any status
    currentRoom->update(game, dt);

    if(currentRoomID == RoomID::Hub && currentRoom->status == RoomStatus::Complete)
    {
        int x = 1;
    }

    // the room will have two flags:
    // status, which indicates a state change in the room, and the world may need to respond
    // nextRoomID, which is only handled in the case of a state change, when the room may request a specific next room

    // if the current room has no status update, then the world doesn't need to get involved
    if (currentRoom->status == RoomStatus::None) return;

    // if the current room is asking to end the game, then just pop that up as a world event and leave
    if (currentRoom->status == RoomStatus::ExitGame)
    {
        pendingEvent = WorldEvent::Exit;
        return;
    }

    // the other room status values include:
    //  complete, indicating this room is finished successfully and shouldn't be reentered (for now)
    //  incomplete, indicating the player left without completing, and will need to restart (for now)
    //  failed, indicating the player failed the room, and will need to restart (for now)

    // all of these indicate we should change rooms, to the one requested or the hub by default
    RoomID const nextRoomID = currentRoom->nextRoomID != RoomID::None ? currentRoom->nextRoomID : RoomID::Hub;

    // so now we know what room we think we'd like to go to, but we should check and prep that room first
    // currentRoom->status = RoomStatus::None;

    // check the next room status, we may need to reinitialize things
    switch (rooms.at(nextRoomID)->status)
    {
    case RoomStatus::Complete:
        return;  // don't go in there, it's done!
    case RoomStatus::Incomplete:
    case RoomStatus::Failed:
        rooms[nextRoomID] = getNewRoomInstance(nextRoomID);  // for now just reinitialize the room entirely!
        break;
    case RoomStatus::None:
        break;
    default:
        break; // the next room shouldn't have an exit game status...
    }

    // now it seems like we can go ahead and change rooms
    changeRoom(nextRoomID);

    // but we should prep that room as needed
    currentRoom->reset();
}

void World::render(Game & game, Renderer & renderer) const
{
    currentRoom->render(game, renderer);
}

void World::changeRoom(RoomID const room)
{
    currentRoomID = room;
    currentRoom = rooms.at(room).get();
}

WorldEvent World::pollEvent() {
    auto const e = pendingEvent;
    pendingEvent = WorldEvent::None;
    return e;
}
