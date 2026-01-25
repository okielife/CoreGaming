#pragma once

#include <filesystem>
#include <map>
#include <unordered_map>

struct _Mix_Music;
struct Mix_Chunk;

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
    { SoundID::Sword, "sword.mp3" }
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
    ~AudioManager();

    /**
     * Deleted copy assignment operator to help ensure a unique instance
     *
     * @return Nothing, this function is deleted
     */
    AudioManager& operator=(const AudioManager&) = delete;

    /**
     * @brief Plays audio based on the ID passed in.
     *
     * If this is the same audio that is already playing, it does nothing.
     * So if you really want to start this audio over, you need to call stop and start.
     * If other audio is currently playing, it stops that audio first, then starts this one
     * By default, this will set the audio to loop forever, but you can specify the number
     * of loops explicitly in the numLoops argument.
     *
     * @param musicIDToPlay The MusicID to be played
     * @param numLoops The number of times to loop the audio, or -1 for continuous (the default)
     */
    void playMusic(MusicID musicIDToPlay, int numLoops = -1);

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

private:
    std::map<MusicID, _Mix_Music *> music;
    MusicID currentMusicID = MusicID::None;
    std::map<SoundID, Mix_Chunk *> sound;
};
