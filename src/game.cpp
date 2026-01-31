#include "game.h"
#include "input.h"
#include "scenes/base.h"
#include "scenes/WizardSpells.h"
#include "scenes/title.h"
#include "scenes/GridShow.h"

Game::Game(Input& input, AudioManager& audio) : input(input), audio(audio)
{
    this->audio.playMusic(MusicID::Area2);

    // build the map of scenes, all in memory all at the beginning
    this->scenes.insert({SceneID::Title, std::make_unique<SceneTitle>(*this)});
    this->scenes.emplace(SceneID::WizardSpells, std::make_unique<SceneWizardSpells>());
    this->scenes.insert({SceneID::GridShow, std::make_unique<SceneGridShow>()});

    // initialize the current scene
    this->currentSceneID = SceneID::Title;
    this->currentScene = this->scenes[this->currentSceneID].get();
}

void Game::update(const float dt)
{
    if (this->currentScene->done)
    {
        switch (this->currentScene->nextScene)
        {
        case SceneID::None:
            // issue error
            break;
        case SceneID::Exit:
            this->running = false;
            break;
        case SceneID::GridShow:
        case SceneID::WizardSpells:
            this->currentSceneID = this->currentScene->nextScene;
            this->currentScene = this->scenes[this->currentSceneID].get();
            break;
        default:
            // issue error
            break;
        }
    }
    this->currentScene->update(*this, dt);
}

void Game::render(Renderer& renderer)
{
    this->currentScene->render(*this, renderer);
}
