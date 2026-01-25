#pragma once

#include <filesystem>
#include <string_view>

/**
 * @file assets.h
 * @brief Centralized helpers for resolving filesystem paths to game assets.
 *
 * As of now this file contains only lightweight path logic
 * and does not perform asset loading or caching.
 *
 * @ingroup assets
 */

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
    static std::filesystem::path root();

    /**
     * @brief Returns the filesystem path to a font asset.
     *
     * @param font_file_name Filename of the font (e.g. "main.ttf").
     * @return Filesystem path to the font asset.
     */
    static std::filesystem::path font(std::string_view font_file_name);

    /**
     * @brief Returns the filesystem path to an audio asset.
     *
     * @param audio_file_name Filename of the audio file (e.g. "theme.ogg").
     * @return Filesystem path to the audio asset.
     */
    static std::filesystem::path audio(std::string_view audio_file_name);

    /**
     * @brief Returns the filesystem path to an image asset.
     *
     * @param image_file_name Filename of the title asset.
     * @return Filesystem path to the title asset.
     */
    static std::filesystem::path image(std::string_view image_file_name);
};
