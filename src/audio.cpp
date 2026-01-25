#include <SDL.h>
#include <SDL2/SDL_mixer.h>

#include "assets.h"
#include "audio.h"

#include <filesystem>
#include <ranges>

AudioManager::AudioManager()
{
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
        throw std::runtime_error(SDL_GetError());
    }

    if (constexpr int requested = MIX_INIT_OGG; (Mix_Init(requested) & requested) != requested) {
        throw std::runtime_error(Mix_GetError());
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 8, 2048) != 0) {
        throw std::runtime_error(Mix_GetError());
    }

    for (auto const & [id, filename] : MusicMap)
    {
        if (id == MusicID::None) continue;
        this->music.insert({id, Mix_LoadMUS(AssetManager::audio(filename).c_str())});
    }

    for (auto const & [id, filename]: SoundMap)
    {
        if (id == SoundID::None) continue;
        this->sound.insert({id, Mix_LoadWAV(AssetManager::audio(filename).c_str())});
    }

}

AudioManager::~AudioManager()
{
    for (const auto& musicPointer : this->music | std::views::values) {
        Mix_FreeMusic(musicPointer);
    }
    Mix_CloseAudio();
    Mix_Quit();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

void AudioManager::playMusic(MusicID const musicIDToPlay, int const numLoops)
{
    if (this->currentMusicID == musicIDToPlay)
    {
        return;  // already playing the current audio, if they really want it restarted, call stop and play
    }
    if (this->currentMusicID != MusicID::None)
    {
        stopMusic();  // if we already have some other audio playing, stop it first
    }
    auto const & musicPointer = this->music[musicIDToPlay];
    Mix_PlayMusic(musicPointer, numLoops);
    this->currentMusicID = musicIDToPlay;
}

void AudioManager::stopMusic()
{
    Mix_HaltMusic();
    this->currentMusicID = MusicID::None;
}

void AudioManager::playSound(SoundID soundIDToPlay)
{
    auto const & soundChunk = this->sound[soundIDToPlay];
    Mix_PlayChannel(-1, soundChunk, 0);
}
