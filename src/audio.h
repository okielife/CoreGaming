#pragma once

#include <filesystem>

#include <SDL2/SDL_mixer.h>

class AudioManager
{
public:
    AudioManager();
    void setAndPlayBackgroundMusic(const std::filesystem::path& musicToPlay);
    void stopBackgroundMusic();
    void changeBackgroundMusic(std::filesystem::path const& musicToPlay);

private:
    Mix_Music *backgroundMusic = nullptr;
};