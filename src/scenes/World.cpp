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

void World::update(Game & game, float dt) {
    currentRoom->update(game, dt);
    if (const auto next = currentRoom->pollExit(); next != RoomID::None) {
        changeRoom(next);
        currentRoom->clearPoll();
        return;
    }
    if (auto outcome = currentRoom->pollOutcome(); outcome == RoomOutcome::LeaveWorld) {
        pendingEvent = WorldEvent::Exit;
    }
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
