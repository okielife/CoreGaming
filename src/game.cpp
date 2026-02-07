#include <game.hpp>
#include <input.hpp>
#include <scenes/WizardSpells.hpp>
#include <scenes/hub.hpp>
#include <scenes/GridShow.hpp>
#include <scenes/Maze.hpp>
#include <scenes/Platformer.hpp>
#include <scenes/BulletHell.hpp>

Game::Game(Input& input, AudioManager& audio) : input(input), audio(audio)
{
    audio.playMusic("area2.wav");
    currentState = std::make_unique<HubState>();
}

void Game::update(const float dt)
{
    currentState->update(*this, dt);
    switch (currentState->pollCommand())
    {
    case GameCommand::None:
        break;
    case GameCommand::Exit:
        running = false;
        return;
    case GameCommand::ReturnToHub:
        currentState = std::make_unique<HubState>();
        break;
    case GameCommand::GridShow:
        currentState = std::make_unique<SceneGridShow>();
        break;
    case GameCommand::WizardSpells:
        currentState = std::make_unique<SceneWizardSpells>();
        break;
    case GameCommand::Maze:
        currentState = std::make_unique<SceneMaze>();
        break;
    case GameCommand::Platformer:
        currentState = std::make_unique<ScenePlatformer>();
        break;
    case GameCommand::BulletHell:
        currentState = std::make_unique<SceneBulletHell>();
        break;
    default:
        throw std::runtime_error("Invalid scene id");
    }
}

void Game::render(Renderer& renderer)
{
    currentState->render(*this, renderer);
}
