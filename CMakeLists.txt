cmake_minimum_required(VERSION 3.28)
project(CoreGaming)
set(CMAKE_CXX_STANDARD 20)

if(UNIX AND NOT APPLE)
    set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
    set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()

# build and setup the sfml libraries
include(FetchContent)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_AUDIO TRUE)
set(SFML_BUILD_GRAPHICS TRUE)
set(SFML_BUILD_NETWORK FALSE)
set(SFML_BUILD_WINDOW TRUE)
set(SFML_INSTALL_PKGCONFIG_FILES FALSE)
set(SFML_INSTALL_PDB FALSE)
if (WIN32)
    set(SFML_STATIC_LIBRARIES ON CACHE BOOL "" FORCE)
else()
    set(SFML_STATIC_LIBRARIES OFF CACHE BOOL "" FORCE)
endif()
FetchContent_Declare(sfml GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.6.1)
FetchContent_MakeAvailable(sfml)

# on MSVC, the min/max macros are expanded and cause compile failures; disable them
if (WIN32)
    add_compile_definitions(NOMINMAX)
endif()

# build the game binary and link it to the SFML libraries
add_executable(game
        # MACOSX_BUNDLE
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
target_link_libraries(game PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)

# after each build, copy the assets from src/assets to build/assets so the assets
# can be found when running in a build tree
add_custom_command(TARGET game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/assets
        $<TARGET_FILE_DIR:game>/assets
)

install(TARGETS game RUNTIME DESTINATION usr/bin)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/assets DESTINATION usr/share/coregaming)
# install(PROGRAMS ${CMAKE_SOURCE_DIR}/packaging/AppRun.in DESTINATION . RENAME AppRun)
install(TARGETS sfml-system sfml-window sfml-graphics sfml-audio LIBRARY DESTINATION usr/lib)
