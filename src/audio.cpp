#include <SDL.h>
#include <SDL2/SDL_mixer.h>

#include "audio.h"

#include <filesystem>

AudioManager::AudioManager()
{
    SDL_Init(SDL_INIT_AUDIO);
    Mix_Init(MIX_INIT_WAVPACK);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void AudioManager::setAndPlayBackgroundMusic(std::filesystem::path const& musicToPlay)
{
    this->backgroundMusic = Mix_LoadMUS(musicToPlay.string().c_str());
    if (!this->backgroundMusic) {
        // Handle error, e.g., printf("Mix_LoadMUS Error: %s\n", Mix_GetError());
    }
    Mix_PlayMusic(this->backgroundMusic, -1);
}

void AudioManager::stopBackgroundMusic()
{
    // Stop music if playing
    Mix_HaltMusic();
    // Free the music data
    Mix_FreeMusic(this->backgroundMusic);
    this->backgroundMusic = nullptr;
}

void AudioManager::changeBackgroundMusic(std::filesystem::path const& musicToPlay)
{
    this->stopBackgroundMusic();
    this->setAndPlayBackgroundMusic(musicToPlay);
}
