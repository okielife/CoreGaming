#include <scenes/CutSceneWizardSpells.hpp>  // TODO: Remove this as a room
#include <scenes/RoomBulletHell.hpp>
#include <scenes/RoomGridShow.hpp>
#include <scenes/RoomHub.hpp>
#include <scenes/RoomMaze.hpp>
#include <scenes/RoomPlatformer.hpp>
#include "scenes/World.hpp"

World::World()
{
    currentRoom = std::make_unique<RoomHub>();
}

void World::update(Game & game, float dt) {
    currentRoom->update(game, dt);
    if (const auto next = currentRoom->pollExit(); next != RoomID::None) {
        changeRoom(game, next);
    }
    if (auto outcome = currentRoom->pollOutcome(); outcome == RoomOutcome::LeaveWorld) {
        pendingEvent = WorldEvent::Exit;
    }
}

void World::render(Game & game, Renderer & renderer)
{
    currentRoom->render(game, renderer);
}

void World::changeRoom(Game & game, RoomID room)
{
    switch (room) {
    case RoomID::Hub:
        currentRoom = std::make_unique<RoomHub>();
        break;

    case RoomID::BulletHell:
        currentRoom = std::make_unique<RoomBulletHell>();
        break;

    case RoomID::Maze:
        currentRoom = std::make_unique<RoomMaze>();
        break;

    case RoomID::GridShow:
        currentRoom = std::make_unique<RoomGridShow>();
        break;

    case RoomID::WizardSpells:
        currentRoom = std::make_unique<RoomWizardSpells>();
        break;

    case RoomID::Platformer:
        currentRoom = std::make_unique<RoomPlatformer>();
        break;

    default:
        throw std::runtime_error("Unknown RoomID in changeRoom");
    }
}

WorldEvent World::pollEvent() {
    auto const e = pendingEvent;
    pendingEvent = WorldEvent::None;
    return e;
}
