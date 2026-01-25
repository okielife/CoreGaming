cmake_minimum_required(VERSION 3.31)
project(CoreGaming)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)

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
        src/textures.cpp
        src/textures.h
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
        ${SDL2_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
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
