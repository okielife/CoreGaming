#include <filesystem>
#include <string_view>

#include <SFML/System.hpp>

#include <assets.h>

#ifdef _WIN32
#    include <Shlwapi.h>
#    include <windows.h>
#else
#    include <unistd.h>
#endif

std::filesystem::path AssetManager::root()
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

std::filesystem::path AssetManager::font(std::string_view const font_file_name)
{
    return root() / "fonts" / font_file_name;
}

std::filesystem::path AssetManager::audio(std::string_view const audio_file_name)
{
    return root() / "audio" / audio_file_name;
}

std::filesystem::path AssetManager::texture(std::string_view const texture_file_name)
{
    return root() / "textures" / texture_file_name;
}

std::filesystem::path AssetManager::sprite(std::string_view const sprite_file_name)
{
    return root() / "sprites" / sprite_file_name;
}