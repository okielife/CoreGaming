// this file is a comment-only file, containing high level doxygen organization,
// like @mainpage and @defgroup stuff

#pragma once

/**
 * @mainpage Core Gaming Engine Documentation
 *
 * Welcome to the game engine source documentation.
 *
 * High-level modules:
 * - @ref game
 * - @ref assets
 * - @ref render
 * - @ref scenes
 * - @ref audio
 * - @ref platform
 */

/**
 * @defgroup game Core Game Engine System
 * @brief Classes related to the game itself
 *
 * These are most likely to be modified as development commences toward a running game
 */

/**
 * @defgroup assets Asset Management
 * @brief Utilities related to locating and managing game assets.
 *
 * The AssetManager provides a collection of stateless utility functions for
 * constructing filesystem paths to assets such as fonts, audio, and title
 * screens. All paths are resolved relative to the executable location using
 * SDL facilities, allowing the game to be run from arbitrary working
 * directories.
 */

/**
 * @defgroup render Rendering Graphics
 * @brief Utilities related to rendering geometry and text to the screen
 *
 * This group contains the files and classes related to rendering.
 * This includes the actual rendering wrapper class as well as the camera(s)
 * and anything else that the client may need to render to the screen.
 */

/**
 * @defgroup scenes Scenes
 * @brief Scenes
 *
 * scenes
 */

/**
 * @defgroup audio Audio
 * @brief Core Gaming Engine Audio Management
 *
 * In Core Gaming Engine, the audio is managed with a relatively simple class. The class
 * initializes every known audio artifact as an SDL asset, allows playing/stopping audio and
 * playing sound effects, and cleans itself up.  Client code utilizes the MusicID enumeration
 * to easily manage the current audio.
 */

/**
 * @defgroup platform Platform Details
 * @brief System/Platform stuff
 *
 * Window, hardware, SDL, etc.
 */