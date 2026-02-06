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
        this->musicMap.emplace(id, path);
    }

    for (auto const & [id, filename]: SoundMap)
    {
        if (id == SoundID::None) continue;
        auto path = AssetManager::audio(filename).string();
        sf::SoundBuffer buffer;
        buffer.loadFromFile(path);
        this->soundMap.insert({id, buffer});
    }
}

void AudioManager::playMusic(MusicID const musicIDToPlay, bool const loop)
{
    if (this->currentMusicID == musicIDToPlay)
    {
        return;  // already playing the current audio, if they really want it restarted, call stop and play
    }
    if (this->currentMusicID != MusicID::None)
    {
        stopMusic();  // if we already have some other audio playing, stop it first
    }
    auto const musicPath = this->musicMap.at(musicIDToPlay);
    this->currentMusicInstance.openFromFile(musicPath);
    this->currentMusicInstance.setLoop(loop);
    this->currentMusicInstance.play();
    this->currentMusicID = musicIDToPlay;
}

void AudioManager::stopMusic()
{
    this->currentMusicInstance.stop();
    this->currentMusicID = MusicID::None;
}

void AudioManager::playSound(const SoundID soundIDToPlay)
{
    sf::Sound sound;
    sound.setBuffer(this->soundMap.at(soundIDToPlay));
    this->currentSounds.push_back(std::move(sound));
    this->currentSounds.back().play();
}

void AudioManager::update()
{
    // remove finished sounds
    std::erase_if(
        this->currentSounds,
        [](const sf::Sound& s) {
            return s.getStatus() == sf::Sound::Stopped;
        }
    );
}