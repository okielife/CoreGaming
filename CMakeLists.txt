cmake_minimum_required(VERSION 3.31)
project(CoreGaming)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

# SDL Root
set(SDL_VERSION        release-2.30.8)
set(SDL_SHARED ON)
set(SDL_STATIC OFF)
set(SDL_TEST OFF)
set(SDL_INSTALL OFF)
FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG        ${SDL_VERSION}
)
FetchContent_MakeAvailable(SDL2)

# SDL Image
set(SDL_IMAGE_VERSION  release-2.8.2)
set(SDL2IMAGE_INSTALL OFF)
set(SDL2IMAGE_SAMPLES OFF)
set(SDL2IMAGE_PNG ON)
set(SDL2IMAGE_JPG OFF)
set(SDL2IMAGE_TIF OFF)
set(SDL2IMAGE_WEBP OFF)
FetchContent_Declare(
        SDL2_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG        ${SDL_IMAGE_VERSION}
)

FetchContent_MakeAvailable(SDL2_image)

# SDL TTF
set(SDL_TTF_VERSION    release-2.24.0)
set(SDL2TTF_INSTALL OFF)
set(SDL2TTF_SAMPLES OFF)
set(SDL2TTF_VENDORED ON) # uses bundled freetype
FetchContent_Declare(
        SDL2_ttf
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
        GIT_TAG        ${SDL_TTF_VERSION}
)

FetchContent_MakeAvailable(SDL2_ttf)

# SDL Mixer
set(SDL_MIXER_VERSION  release-2.8.0)
set(SDL2MIXER_INSTALL OFF)
set(SDL2MIXER_SAMPLES OFF)
set(SDL2MIXER_WAV ON)
set(SDL2MIXER_OGG OFF)
set(SDL2MIXER_MP3 OFF)
set(SDL2MIXER_FLAC OFF)
set(SDL2MIXER_MOD OFF)
set(SDL2MIXER_OPUS OFF)
set(SDL2MIXER_MIDI OFF)
set(SDL2MIXER_VENDORED ON)
FetchContent_Declare(
        SDL2_mixer
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
        GIT_TAG        ${SDL_MIXER_VERSION}
)
FetchContent_MakeAvailable(SDL2_mixer)


add_executable(game
        src/assets.h
        src/audio.cpp
        src/audio.h
        src/camera.h
        src/constants.h
        src/game.cpp
        src/game.h
        src/input.cpp
        src/input.h
        src/main.cpp
        src/platform.cpp
        src/platform.h
        src/renderer.cpp
        src/renderer.h
        src/scenes/base.h
        src/scenes/level1.cpp
        src/scenes/level1.h
        src/scenes/title.cpp
        src/scenes/title.h
        src/doxygen.h
        src/assets.cpp
)
target_include_directories(game PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
)

target_link_libraries(game PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
        SDL2_mixer::SDL2_mixer
)

add_custom_command(TARGET game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/assets
        $<TARGET_FILE_DIR:game>/assets
)

install(TARGETS game
        RUNTIME DESTINATION bin
)

install(DIRECTORY src/assets/
        DESTINATION bin/assets
)

option(BUILD_TESTING "Turn this ON to enable testing" ON)
if (BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif ()
