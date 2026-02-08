#pragma once

#include <filesystem>

#include <SFML/Audio.hpp>

/**
 * @file audio.hpp
 * @brief Centralized helpers for managing and playing audio in the game.
 *
 * @ingroup audio
 */

/**
 * @brief Audio management class for audio and sound effects
 *
 * This class will provide everything needed to manage SFML music and sound,
 * with workers to start/stop/pause/etc.
 *
 * @ingroup audio
 */
class AudioManager
{
public:

    /**
     * @brief Loads and plays music based on the name passed in.
     *
     * If this is the same music that is already playing, it does nothing.
     * So if you really want to start this music over, you need to call stop and start.
     * If other music is currently playing, it stops that music first, then starts this one
     * By default, this will set the music to loop forever, but that can be disabled by
     * passing loop = false.
     *
     * @param music_file_name The filename of the music to be played, use AssetManager::Naming helpers
     * @param loop A flag for whether to loop the music or not, defaults to true
     */
    void playMusic(std::string const & music_file_name, bool loop = true);

    /**
     * @brief Stops any audio currently playing
     */
    void stopMusic();

    /**
     * @brief Plays a sound effect based on the name passed in
     *
     * @param sound_file_name The filename of the sound to be played, use AssetManager::Naming helpers
     */
    void playSound(std::string const & sound_file_name);

    /**
     * @brief An update routine to regularly flush completed sound effects
     *
     * Call this routine in the normal game update loop
     */
    void update();

private:
    std::string currentMusic;
    sf::Music currentMusicInstance;
    std::vector<sf::Sound> currentSounds;
};
