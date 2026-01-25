#pragma once

#include <filesystem>
#include <string_view>

#include <SDL2/SDL.h>

#include "assets.h"

std::filesystem::path AssetManager::root()
{
    char* base = SDL_GetBasePath();
    std::filesystem::path const root = base ? base : ".";
    SDL_free(base);
    return root / "assets";
}

std::filesystem::path AssetManager::font(std::string_view const font_file_name)
{
    return root() / "fonts" / font_file_name;
}

std::filesystem::path AssetManager::audio(std::string_view const audio_file_name)
{
    return root() / "audio" / audio_file_name;
}

std::filesystem::path AssetManager::image(std::string_view const image_file_name)
{
    return root() / "image" / image_file_name;
}
