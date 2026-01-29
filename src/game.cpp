#include "game.h"
#include "input.h"
#include "scenes/base.h"
#include "scenes/opening.h"
#include "scenes/title.h"
#include "scenes/level1.h"

Game::Game(Input& input, AudioManager& audio) : input(input), audio(audio) {
    this->audio.playMusic(MusicID::Area2);

    // build the map of scenes, all in memory all at the beginning
    this->scenes.insert({SceneID::Title, std::make_unique<SceneTitle>(*this)});
    this->scenes.emplace(SceneID::Opening, std::make_unique<Opening>());
    this->scenes.insert({SceneID::Level1, std::make_unique<SceneLevel1>()});

    // initialize the current scene
    this->currentSceneID = SceneID::Title;
    this->currentScene = this->scenes[this->currentSceneID].get();
}

void Game::update(const float dt)
{
    if (this->currentScene->done) {
        switch (this->currentSceneID)
        {
        case SceneID::Title:
            this->currentSceneID = SceneID::Opening;
            this->currentScene = this->scenes[this->currentSceneID].get();
            break;
        case SceneID::Opening:
            this->currentSceneID = SceneID::Level1;
            this->currentScene = this->scenes[this->currentSceneID].get();
            break;
        case SceneID::Level1:
            this->running = false;
            break;
        default:
            break;
        }
    }
    this->currentScene->update(*this, dt);
}

void Game::render(Renderer & renderer)
{
    this->currentScene->render(*this, renderer);
}
