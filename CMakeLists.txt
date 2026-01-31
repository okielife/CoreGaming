cmake_minimum_required(VERSION 3.31)
project(CoreGaming)
set(CMAKE_CXX_STANDARD 20)

# build and setup the sfml libraries
include(cmake/sfml.cmake)

# build the game binary and link it to the SFML libraries
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
        src/scenes/GridShow.cpp
        src/scenes/GridShow.h
        src/scenes/title.cpp
        src/scenes/title.h
        src/doxygen.h
        src/assets.cpp
        src/scenes/WizardSpells.cpp
        src/scenes/WizardSpells.h
)
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
