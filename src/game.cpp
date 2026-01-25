#include "constants.h"
#include "assets.h"
#include "game.h"
#include "input.h"
#include "scenes/base.h"
#include "scenes/title.h"
#include "scenes/level1.h"

Game::Game(Renderer& renderer, Input& input, AudioManager& audio) : renderer(renderer), input(input), audio(audio) {
    this->audio.playMusic(MusicID::Area2);

    // build the map of scenes, all in memory all at the beginning
    this->scenes.insert({SceneID::Title, std::move(std::make_unique<SceneTitle>(*this))});
    this->scenes.insert({SceneID::Level1, std::move(std::make_unique<SceneLevel1>())});

    // initialize the current scene
    this->currentSceneID = SceneID::Title;
    this->currentScene = this->scenes[this->currentSceneID].get();
}

void Game::frame(const float dt_ms)
{
    this->update(dt_ms);
    this->currentScene->update(*this, dt_ms);
    this->currentScene->render((*this));
}

void Game::update([[maybe_unused]] const float dt_ms)
{
    if (this->currentScene->done) {
        switch (this->currentSceneID)
        {
        case SceneID::Title:
            this->currentSceneID = SceneID::Level1;
            this->currentScene = this->scenes[this->currentSceneID].get();
            break;
        case SceneID::Level1:
            this->running = false;
            break;
        default:
            return;
        }
    }
}

