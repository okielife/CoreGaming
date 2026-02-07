#include <game.hpp>
#include <input.hpp>
#include <scenes/WizardSpells.hpp>
#include <scenes/title.hpp>
#include <scenes/GridShow.hpp>
#include <scenes/Maze.hpp>
#include <scenes/Platformer.hpp>
#include <scenes/BulletHell.hpp>

Game::Game(Input& input, AudioManager& audio) : input(input), audio(audio)
{
    audio.playMusic("area2.wav");
    currentScene = new SceneTitle();  // initialize the current scene
}

void Game::update(const float dt)
{
    if (currentScene && currentScene->done)
    {
        SceneBase * nextScene;
        switch (currentScene->nextScene)
        {
        case SceneID::None:
            throw std::runtime_error("Invalid scene id None");
        case SceneID::Exit:
            running = false;
            return;
        case SceneID::Title:
            nextScene = new SceneTitle();
            break;
        case SceneID::GridShow:
            nextScene = new SceneGridShow();
            break;
        case SceneID::WizardSpells:
            nextScene = new SceneWizardSpells();
            break;
        case SceneID::Maze:
            nextScene = new SceneMaze();
            break;
        case SceneID::Platformer:
            nextScene = new ScenePlatformer();
            break;
        case SceneID::BulletHell:
            nextScene = new SceneBulletHell();
            break;
        default:
            throw std::runtime_error("Invalid scene id");
        }
        delete currentScene;
        currentScene = nextScene;
    }
    if (currentScene) currentScene->update(*this, dt);
}

void Game::render(Renderer& renderer)
{
    currentScene->render(*this, renderer);
}
