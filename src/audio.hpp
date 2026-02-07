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
 * This class will provide everything needed to manage SDL audio and audio
 * instances, and workers to start/stop/pause/etc. the sounds.  Note that there
 * must only ever be one audio manager instance created, as it makes
 * calls to SDL init routines that should not be repeated.
 *
 * @ingroup audio
 */
class AudioManager
{
public:

    AudioManager() = default;

    /**
     * @brief Deleted copy constructor
     *
     * Deleted copy constructor to help ensure a unique instance
     */
    AudioManager(const AudioManager&) = delete;

    /**
     * @brief Audio manager destructor
     *
     * Audio manager destructor must free any owned assets and shut down the SDL audio subsystem.
     */
    ~AudioManager() = default;

    /**
     * Deleted copy assignment operator to help ensure a unique instance
     *
     * @return Nothing, this function is deleted
     */
    AudioManager& operator=(const AudioManager&) = delete;

    /**
     * @brief Plays music based on the ID passed in.
     *
     * If this is the same music that is already playing, it does nothing.
     * So if you really want to start this music over, you need to call stop and start.
     * If other music is currently playing, it stops that music first, then starts this one
     * By default, this will set the music to loop forever, but that can be disabled by
     * passing loop = false.
     *
     * @param music_file_name The MusicID to be played
     * @param loop A flag for whether to loop the music or not, defaults to true
     */
    void playMusic(std::string const & music_file_name, bool loop = true);

    /**
     * @brief Stops any audio currently playing
     *
     * Internally this resets the audio ID tracking, but mostly it just shuts down the audio
     */
    void stopMusic();

    /**
     * @brief Plays sound based on the ID passed in
     *
     * @param sound_file_name The SoundID to be played
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
