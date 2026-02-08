#pragma once

#include <string_view>

constexpr auto WINDOW_TITLE = "Core Gaming in Action";
constexpr int WINDOW_WIDTH = 800; // TODO: Change these, test and fix all the games to work on any resolution
constexpr int WINDOW_HEIGHT = 600;

/**
 * @brief Constants for asset names to catch typos at compile time.
 *
 * A small static-only and constexpr set of strings, one for each file in the
 * "assets" directory.  Using these variables instead of hardcoded strings will
 * ensure that any typos are caught early at compile time.
 */
struct AssetNaming
{
    // Fonts
    static constexpr std::string_view FontJolly = "jolly.ttf";
    static constexpr std::string_view FontUbuntu = "ubuntu.ttg";
    // Music
    static constexpr std::string_view MusicArea2 = "area2.wav";
    // Sounds
    static constexpr std::string_view SoundSword = "sword.wav";
    // Textures
    static constexpr std::string_view TextureSky = "sky.png";
    static constexpr std::string_view TextureWizard = "wizard.png";
};
