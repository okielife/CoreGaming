#include <game.h>
#include <input.h>
#include <scenes/WizardSpells.h>
#include <scenes/title.h>
#include <scenes/GridShow.h>
#include <scenes/Maze.h>
// #include <scenes/Platformer.h>
#include <scenes/BulletHell.h>

Game::Game(Input& input, AudioManager& audio) : input(input), audio(audio)
{
    this->audio.playMusic(MusicID::Area2);
    // initialize the current scene
    this->currentScene = new SceneTitle();
}

void Game::update(const float dt)
{
    if (this->currentScene && this->currentScene->done)
    {
        SceneBase * nextScene;
        switch (this->currentScene->nextScene)
        {
        case SceneID::None:
            throw std::runtime_error("Invalid scene id None");
        case SceneID::Exit:
            this->running = false;
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
        // case SceneID::Platformer:
        //     nextScene = new ScenePlatformer();
        //     break;
        case SceneID::BulletHell:
            nextScene = new SceneBulletHell();
            break;
        default:
            throw std::runtime_error("Invalid scene id");
        }
        delete this->currentScene;
        this->currentScene = nextScene;
    }
    if (this->currentScene) this->currentScene->update(*this, dt);
}

void Game::render(Renderer& renderer)
{
    this->currentScene->render(*this, renderer);
}
