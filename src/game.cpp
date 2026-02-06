#include <game.h>
#include <input.h>
// #include <scenes/base.h>
#include <scenes/WizardSpells.h>
// #include <scenes/title.h>
// #include <scenes/GridShow.h>
// #include <scenes/Maze.h>
// #include <scenes/Platformer.h>
#include <scenes/BulletHell.h>

Game::Game(Input& input, AudioManager& audio) : input(input), audio(audio)
{
    this->audio.playMusic(MusicID::Area2);

    // build the map of scenes, all in memory all at the beginning
    // this->scenes.insert({SceneID::Title, std::make_unique<SceneTitle>(*this)});
    // this->scenes.emplace(SceneID::WizardSpells, std::make_unique<SceneWizardSpells>());
    // // this->scenes.insert({SceneID::GridShow, std::make_unique<SceneGridShow>()});
    // // this->scenes.insert({SceneID::Maze, std::make_unique<SceneMaze>()});
    // // this->scenes.insert({SceneID::Platformer, std::make_unique<ScenePlatformer>()});
    // this->scenes.insert({SceneID::BulletHell, std::make_unique<SceneBulletHell>()});

    // initialize the current scene
    this->currentScene = new SceneWizardSpells();
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
        // case SceneID::Title:
        //     nextScene = new SceneTitle(*this);
        //     break;
        // case SceneID::GridShow:
        //     nextScene = new SceneGridShow();
        //     break;
        case SceneID::WizardSpells:
            nextScene = new SceneWizardSpells();
            break;
        // case SceneID::Maze:
        //     nextScene = new SceneMaze();
        //     break;
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
