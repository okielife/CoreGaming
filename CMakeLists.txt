cmake_minimum_required(VERSION 3.31)
project(CoreGaming)
set(CMAKE_CXX_STANDARD 20)

# build and setup the sfml libraries
include(cmake/sfml.cmake)

# on MSVC, the min/max macros are expanded and cause compile failures; disable them
if (WIN32)
    add_compile_definitions(NOMINMAX)
endif()

# build the game binary and link it to the SFML libraries
add_executable(game
        src/assets.hpp
        src/audio.cpp
        src/audio.hpp
        src/camera.hpp
        src/collision.hpp
        src/command.hpp
        src/constants.hpp
        src/doxygen.hpp
        src/drawables.hpp
        src/game.cpp
        src/game.hpp
        src/input.cpp
        src/input.hpp
        src/main.cpp
        src/platform.cpp
        src/platform.hpp
        src/renderer.cpp
        src/renderer.hpp
        src/scenes/CutSceneWizardSpells.cpp
        src/scenes/CutSceneWizardSpells.hpp
        src/scenes/RoomBase.hpp
        src/scenes/RoomBulletHell.cpp
        src/scenes/RoomBulletHell.hpp
        src/scenes/RoomGridShow.cpp
        src/scenes/RoomGridShow.hpp
        src/scenes/RoomHub.cpp
        src/scenes/RoomHub.hpp
        src/scenes/RoomMaze.hpp
        src/scenes/RoomMaze.cpp
        src/scenes/RoomPlatformer.hpp
        src/scenes/RoomPlatformer.cpp
        src/scenes/StateBase.hpp
        src/scenes/StatePause.hpp
        src/scenes/StatePlaying.cpp
        src/scenes/StatePlaying.hpp
        src/scenes/World.hpp
        src/scenes/World.cpp
)
target_include_directories(game PRIVATE src)
target_link_libraries(game PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
)

# after each build, copy the assets from src/assets to build/assets so the assets
# can be found when running in a build tree
add_custom_command(TARGET game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/assets
        $<TARGET_FILE_DIR:game>/assets
)

# at install time the game will be in bin/ and the assets will be in bin/assets
# this ensures that the assets can always be found at executable_path.parent / assets
install(TARGETS game RUNTIME DESTINATION bin)
install(DIRECTORY src/assets/ DESTINATION bin/assets)

# enable unit testing
# enable_testing()
# add_subdirectory(tests)
