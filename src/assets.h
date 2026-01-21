#pragma once

#include <filesystem>
#include <string_view>

#include <SDL2/SDL.h>

struct AssetManager
{
    static std::filesystem::path asset_root()
    {
        char* base = SDL_GetBasePath(); // directory of executable
        std::filesystem::path root = base ? base : ".";
        SDL_free(base);

        return root / "assets";
    }

    static std::filesystem::path font(std::string_view const font_file_name)
    {
        return asset_root() / "fonts" / font_file_name;
    }

    static std::filesystem::path music(std::string_view const music_file_name)
    {
        return asset_root() / "music" / music_file_name;
    }
};
