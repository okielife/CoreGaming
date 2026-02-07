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
 * @brief Centralized helpers for resolving filesystem paths to game assets.
 *
 * As of now this file contains only lightweight path logic
 * and does not perform asset loading or caching.
 *
 * @ingroup assets
 */


inline std::unordered_map<std::string, sf::Texture> textures;
inline std::unordered_map<std::string, sf::Font> fonts;
inline std::unordered_map<std::string, sf::SoundBuffer> soundBufferCache;

/**
 * @brief Stateless helper for resolving asset filesystem paths.
 *
 * AssetManager provides static functions that return filesystem paths to
 * various categories of assets. It does not own or cache assets and is safe
 * to use anywhere in the codebase.
 *
 * @ingroup assets
 */
struct AssetManager
{
    /**
     * @brief Returns the root directory containing all game assets.
     *
     * The asset root is computed relative to the directory of the running
     * executable using SDL_GetBasePath(). This allows assets to be located
     * correctly regardless of the process working directory.
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
        ssize_t len = readlink("/proc/self/exe", executableRelativePath, sizeof(executableRelativePath) - 1);
        executableRelativePath[len] = '\0';
#elif _WIN32
        GetModuleFileName(NULL, executableRelativePath, sizeof(executableRelativePath));
#endif
        std::filesystem::path const exe = executableRelativePath;
        return exe.parent_path() / "assets";
    }

    /**
     * @brief Returns the filesystem path to a font asset.
     *
     * @param font_file_name Filename of the font (e.g. "main.ttf").
     * @return Filesystem path to the font asset.
     */
    static sf::Font font(std::string const & font_file_name)
    {
        auto const it = fonts.find(font_file_name);
        if (it != fonts.end())
            return it->second;
        auto& font = fonts.emplace(font_file_name, sf::Font{}).first->second;
        font.loadFromFile(root() / "fonts" / font_file_name);
        return font;
    }

    /**
     * @brief Returns the filesystem path to a music asset.
     *
     * @param music_file_name Filename of the music file (e.g. "theme.ogg").
     * @return Filesystem path to the music asset.
     */
    static std::filesystem::path music(std::string_view const music_file_name)
    {
        return root() / "music" / music_file_name;
    }

    /**
     *
     * @param sound_file_name Filename of the sound asset (e.g. "sword.mps")
     * @return A loaded (possibly from cache) sound buffer asset
     */
    static sf::SoundBuffer & sound(std::string const & sound_file_name) {
        auto const it = soundBufferCache.find(sound_file_name);
        if (it != soundBufferCache.end())
            return it->second;
        auto& sound = soundBufferCache.emplace(sound_file_name, sf::SoundBuffer{}).first->second;
        sound.loadFromFile(root() / "sound" / sound_file_name);
        return sound;
    }

    /**
     * @brief Returns the texture asset with the given name
     *
     * Note that in this context, a texture is "what" we want to draw.
     * Whereas a sprite is "how" we draw it.
     * Eventually, we could add a second argument here for a subdirectory category inside textures/
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
        tex.loadFromFile(root() / "textures" / texture_file_name);
        return tex;
    }

};
