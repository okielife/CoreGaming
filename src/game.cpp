#include <game.hpp>
#include <input.hpp>
#include <iostream>
#include <scenes/StatePlaying.hpp>

Game::Game(Input& input, AudioManager& audio) : input(input), audio(audio)
{
    audio.playMusic("area2.wav");
    currentState = std::make_unique<StatePlaying>();
}

void Game::update(const float dt)
{
    // This routine checks very high level commands - What global mode am I in?
    currentState->update(*this, dt);
    switch (currentState->pollCommand())
    {
    case GameCommand::None:
        break;
    case GameCommand::Exit: // Should make these a different command enum
        running = false;
        return;
    case GameCommand::PushPause:
        std::cout << "Opening pause overlay" << std::endl;
        break;
    case GameCommand::PopPause:
        std::cout << "Closing pause overlay" << std::endl;
        break;

        // case GameCommand::ReturnToHub:
    //     currentState = std::make_unique<HubWorld>();
    //     break;
    // case GameCommand::GridShow:
    //     currentState = std::make_unique<SceneGridShow>();
    //     break;
    // case GameCommand::WizardSpells:
    //     currentState = std::make_unique<SceneWizardSpells>();
    //     break;
    // case GameCommand::Maze:
    //     currentState = std::make_unique<RoomMaze>();
    //     break;
    // case GameCommand::Platformer:
    //     currentState = std::make_unique<ScenePlatformer>();
    //     break;
    // case GameCommand::BulletHell:
    //     currentState = std::make_unique<RoomBulletHell>();
    //     break;
    // default:
    //     throw std::runtime_error("Invalid scene id");
    }
}

void Game::render(Renderer& renderer)
{
    currentState->render(*this, renderer);
}
