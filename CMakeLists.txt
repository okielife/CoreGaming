cmake_minimum_required(VERSION 3.31)
project(CoreGaming)
set(CMAKE_CXX_STANDARD 20)

# build and setup the sfml libraries
include(cmake/sfml.cmake)

# build the game binary and link it to the SFML libraries
add_executable(game
        src/assets.hpp
        src/audio.cpp
        src/audio.hpp
        src/camera.hpp
        src/constants.hpp
        src/doxygen.hpp
        src/game.cpp
        src/game.hpp
        src/collision.hpp
        src/input.cpp
        src/input.hpp
        src/main.cpp
        src/platform.cpp
        src/platform.hpp
        src/renderer.cpp
        src/renderer.hpp
        src/scenes/base.hpp
        src/scenes/GridShow.cpp
        src/scenes/GridShow.hpp
        src/scenes/title.cpp
        src/scenes/title.hpp
        src/scenes/WizardSpells.cpp
        src/scenes/WizardSpells.hpp
        src/scenes/Maze.hpp
        src/scenes/Maze.cpp
        src/scenes/Platformer.hpp
        src/scenes/Platformer.cpp
        src/scenes/BulletHell.cpp
        src/scenes/BulletHell.hpp
        src/drawables.hpp
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
