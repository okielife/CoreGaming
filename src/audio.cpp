#include <filesystem>

#include <SFML/Audio.hpp>

#include <assets.h>
#include <audio.h>


AudioManager::AudioManager()
{
    for (auto const & [id, filename] : MusicMap)
    {
        if (id == MusicID::None) continue;
        auto path = AssetManager::audio(filename).string();
        musicMap.emplace(id, path);
    }

    for (auto const & [id, filename]: SoundMap)
    {
        if (id == SoundID::None) continue;
        auto path = AssetManager::audio(filename).string();
        sf::SoundBuffer buffer;
        buffer.loadFromFile(path);
        soundMap.insert({id, buffer});
    }
}

void AudioManager::playMusic(MusicID const musicIDToPlay, bool const loop)
{
    if (currentMusicID == musicIDToPlay)
    {
        return;  // already playing the current audio, if they really want it restarted, call stop and play
    }
    if (currentMusicID != MusicID::None)
    {
        stopMusic();  // if we already have some other audio playing, stop it first
    }
    auto const musicPath = musicMap.at(musicIDToPlay);
    currentMusicInstance.openFromFile(musicPath);
    currentMusicInstance.setLoop(loop);
    currentMusicInstance.play();
    currentMusicID = musicIDToPlay;
}

void AudioManager::stopMusic()
{
    currentMusicInstance.stop();
    currentMusicID = MusicID::None;
}

void AudioManager::playSound(const SoundID soundIDToPlay)
{
    sf::Sound sound;
    sound.setBuffer(soundMap.at(soundIDToPlay));
    currentSounds.push_back(std::move(sound));
    currentSounds.back().play();
}

void AudioManager::update()
{
    // remove finished sounds
    std::erase_if(
        currentSounds,
        [](const sf::Sound& s) {
            return s.getStatus() == sf::Sound::Stopped;
        }
    );
}