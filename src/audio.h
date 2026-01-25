#pragma once

#include <filesystem>
#include <map>
#include <unordered_map>

#include <SFML/Audio.hpp>

/**
 * @file audio.h
 * @brief Centralized helpers for managing and playing audio in the game.
 *
 * @ingroup audio
 */

/**
 * The enumerated music IDs, should be one per available music in the assets.
 */
enum class MusicID
{
    None,
    Area2
};

/**
 * A mapping of the music ID to the filename in the assets/audio directory.
 * Update this accordingly whenever music is added/changed/removed
 */
inline const std::unordered_map<MusicID, std::string> MusicMap = {
    { MusicID::Area2, "area2.wav" }
};

/**
 * The enumerated sound IDs, should be one per available sound in the assets.
 */
enum class SoundID
{
    None,
    Sword
};

/**
 * A mapping of the sound ID to the filename in the assets/audio directory.
 * Update this accordingly whenever sound is added/changed/removed
 */
inline const std::unordered_map<SoundID, std::string> SoundMap = {
    { SoundID::Sword, "sword.wav" }
};

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
    /**
     * @brief Primary constructor for the audio manager class
     *
     * This constructor:
     * - calls the audio subsystem initialization routines
     * - establishes which decoders are initialized
     * - sets up the mixer
     * - declares the number of audio channels that may ultimately be used by the game
     * - instantiates all known audio class instances (inefficient but easy)
     */
    AudioManager();

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
     * @param musicIDToPlay The MusicID to be played
     * @param loop A flag for whether to loop the music or not, defaults to true
     */
    void playMusic(MusicID musicIDToPlay, bool loop = true);

    /**
     * @brief Stops any audio currently playing
     *
     * Internally this resets the audio ID tracking, but mostly it just shuts down the audio
     */
    void stopMusic();

    /**
     * @brief Plays sound based on the ID passed in
     *
     * @param soundIDToPlay The SoundID to be played
     */
    void playSound(SoundID soundIDToPlay);

    /**
     * @brief An update routine to regularly flush completed sound effects
     *
     * Call this routine in the normal game update loop
     */
    void update();

private:
    MusicID currentMusicID = MusicID::None;
    std::map<MusicID, std::string> musicMap;
    sf::Music currentMusicInstance;
    std::map<SoundID, sf::SoundBuffer> soundMap;
    std::vector<sf::Sound> currentSounds;
};
