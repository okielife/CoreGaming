#pragma once

#include <filesystem>
#include <unordered_map>
#include <string_view>

#ifdef _WIN32
#    include <Shlwapi.h>
#    include <windows.h>
#else
#    include <unistd.h>
#endif

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/**
 * @file assets.hpp
 * @brief Centralized helpers for providing game assets.
 *
 * This file contains static (global) storage of the current
 * asset types, which includes fonts, sound buffers, and textures.
 *
 * @note The music asset is a simple filesystem path because it is read on-demand
 *
 * @ingroup assets
 */

/**
 * @brief Static (inline, global) storage of font assets
 */
inline std::unordered_map<std::string_view, sf::Font> fonts;

/**
 * @brief Static (inline, global) storage of sound buffer assets
 */
inline std::unordered_map<std::string, sf::SoundBuffer> soundBufferCache;

/**
 * @brief Static (inline, global) storage of texture assets
 */
inline std::unordered_map<std::string, sf::Texture> textures;

/**
 * @brief Asset manager for the game instance.
 *
 * AssetManager provides static functions that return appropriate assets based on
 * the asset type.  It owns assets, where appropriate, in static storage to avoid
 * requiring an AssetManager instance to be passed around.
 *
 * @ingroup assets
 */
struct AssetManager
{
    /**
     * @brief Returns the root directory containing all game assets.
     *
     * The asset root is computed relative to the directory of the running
     * executable using OS-specific techniques. This allows assets to be located
     * correctly regardless of the process working directory.
     *
     * @note In the CMake build system, the assets folder is copied into the build tree
     *       so that the game works fine in the build tree.
     *
     * @return Filesystem path to the asset root directory.
     */
    static std::filesystem::path root()
    {
        char executableRelativePath[1024];
        // #ifdef __APPLE__
        //     uint32_t pathSize = sizeof(executableRelativePath);
        //     _NSGetExecutablePath(executableRelativePath, &pathSize);
#ifdef __linux__
        if (const char* appdir = std::getenv("APPDIR")) {
            // we are running from the AppImage launcher, so APPDIR gives us the root of the appimage bundle
            auto const p =  std::filesystem::path(appdir) / "usr" / "share" / "coregaming" / "assets";
            return std::filesystem::weakly_canonical(p);
        }
        const ssize_t len = readlink("/proc/self/exe", executableRelativePath, sizeof(executableRelativePath) - 1);
        executableRelativePath[len] = '\0';
        const std::filesystem::path exePath = executableRelativePath;
        const std::filesystem::path exeDir  = exePath.parent_path();
        const std::filesystem::path assetsDirNextToBinary = exeDir / "assets";
        if (std::filesystem::exists(assetsDirNextToBinary)) {
            // we are running from the cmake build tree, and we pull the assets right next to the binary
            return std::filesystem::weakly_canonical(assetsDirNextToBinary);
        }
        // really the only other option is that we are running as a raw executable right from the installation bundle
        auto const p = exeDir.parent_path().parent_path() / "usr" / "share" / "coregaming" / "assets";
        return std::filesystem::weakly_canonical(p);
#elif _WIN32
        GetModuleFileName(NULL, executableRelativePath, sizeof(executableRelativePath));
#endif
        // std::filesystem::path const exe = executableRelativePath;

    }

    /**
     * @brief Returns an `sf::Font` asset with the given name
     *
     * @param font_file_name Filename of the font (e.g. "main.ttf").
     * @return A loaded (possibly from cache) font asset
     */
    static sf::Font font(std::string_view font_file_name)
    {
        auto const it = fonts.find(font_file_name);
        if (it != fonts.end())
            return it->second;
        auto& font = fonts.emplace(font_file_name, sf::Font{}).first->second;
        auto const fullPath = root() / "fonts" / font_file_name;
        std::string const fullPathString = fullPath.string();
        font.loadFromFile(fullPathString);
        return font;
    }

    /**
     * @brief Returns the filesystem path to a music asset with the given name
     *
     * This is different from other asset functions, which usually return
     * asset instances themselves.  Music is streamed directly from the disk,
     * so it doesn't make much sense to try to return anything but the path.
     *
     * @param music_file_name Filename of the music file (e.g. "theme.ogg").
     * @return Filesystem path to the music asset.
     */
    static std::filesystem::path music(std::string_view const music_file_name)
    {
        return root() / "music" / music_file_name;
    }

    /**
     * @brief Returns an `sf::SoundBuffer` asset with the given name
     *
     * @param sound_file_name Filename of the sound asset (e.g. "sword.mps")
     * @return A loaded (possibly from cache) sound buffer asset
     */
    static sf::SoundBuffer & sound(std::string const & sound_file_name) {
        auto const it = soundBufferCache.find(sound_file_name);
        if (it != soundBufferCache.end())
            return it->second;
        auto& sound = soundBufferCache.emplace(sound_file_name, sf::SoundBuffer{}).first->second;
        auto const fullPath = root() / "sound" / sound_file_name;
        std::string const fullPathString = fullPath.string();
        sound.loadFromFile(fullPathString);
        return sound;
    }

    /**
     * @brief Returns an `sf::Texture` asset with the given name
     *
     * Note that in this context, a texture is "what" we want to draw.
     * Whereas a sprite is "how" we draw it.
     * As the list of textures grows, we could add a textures/something directory,
     * which would lead to a second argument to this function for the
     * category/subdirectory name
     *
     * @param texture_file_name Filename of the texture asset.
     * @return A loaded (possibly from cache) texture asset.
     */
    static sf::Texture texture(std::string const & texture_file_name)
    {
        auto const it = textures.find(texture_file_name);
        if (it != textures.end())
            return it->second;
        auto& tex = textures.emplace(texture_file_name, sf::Texture{}).first->second;
        auto const fullPath = root() / "textures" / texture_file_name;
        std::string const fullPathString = fullPath.string();
        tex.loadFromFile(fullPathString);
        return tex;
    }

};
