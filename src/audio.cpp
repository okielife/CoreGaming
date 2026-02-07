#include <filesystem>

#include <SFML/Audio.hpp>

#include <assets.hpp>
#include <audio.hpp>

void AudioManager::playMusic(std::string const & music_file_name, bool const loop)
{
    if (currentMusic == music_file_name)
    {
        return;  // already playing the current audio, if they really want it restarted, call stop and play
    }
    if (!currentMusic.empty())
    {
        stopMusic();  // if we already have some other audio playing, stop it first
    }
    auto const musicPath = AssetManager::music(music_file_name);
    currentMusicInstance.openFromFile(musicPath);
    currentMusicInstance.setLoop(loop);
    currentMusicInstance.play();
    currentMusic = music_file_name;
}

void AudioManager::stopMusic()
{
    currentMusicInstance.stop();
    currentMusic = "";
}

void AudioManager::playSound(std::string const & sound_file_name)
{
    sf::Sound sound;
    auto const & buffer = AssetManager::sound(sound_file_name);
    sound.setBuffer(buffer);
    currentSounds.push_back(std::move(sound));
    currentSounds.back().play();
}

void AudioManager::update()
{
    for (auto it = currentSounds.begin(); it != currentSounds.end(); )
    {
        if (it->getStatus() == sf::Sound::Stopped && it->getPlayingOffset() > sf::Time::Zero)
        {
            it = currentSounds.erase(it);;
        } else
        {
            ++it;
        }
    }
}