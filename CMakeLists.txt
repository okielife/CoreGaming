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
set(SFML_BUILD_WINDOW TRUE)
set(SFML_INSTALL_PKGCONFIG_FILES FALSE)
set(SFML_INSTALL_PDB FALSE)
set(SFML_INSTALL OFF CACHE BOOL "" FORCE)
set(SFML_SKIP_INSTALL ALL CACHE BOOL "" FORCE) # works on newer SFML
#if (WIN32)
#    set(SFML_STATIC_LIBRARIES ON CACHE BOOL "" FORCE)
#else()
    set(SFML_STATIC_LIBRARIES OFF CACHE BOOL "" FORCE)
#endif()
FetchContent_Declare(sfml GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.6.1)
FetchContent_MakeAvailable(sfml)

# on MSVC, the min/max macros are expanded and cause compile failures; disable them
if (WIN32)
    add_compile_definitions(NOMINMAX)
endif()

# build the game binary and link it to the SFML libraries
add_executable(coregaming
        MACOSX_BUNDLE
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
        src/rooms/RoomBase.hpp
        src/rooms/RoomBulletHell.cpp
        src/rooms/RoomBulletHell.hpp
        src/rooms/RoomGridShow.cpp
        src/rooms/RoomGridShow.hpp
        src/rooms/RoomHub.cpp
        src/rooms/RoomHub.hpp
        src/rooms/RoomMaze.hpp
        src/rooms/RoomMaze.cpp
        src/rooms/RoomPlatformer.hpp
        src/rooms/RoomPlatformer.cpp
        src/states/StateBase.hpp
        src/states/StatePause.hpp
        src/states/StatePlaying.cpp
        src/states/StatePlaying.hpp
        src/worlds/World.hpp
        src/worlds/World.cpp
)
target_include_directories(coregaming PRIVATE src)
target_link_libraries(coregaming PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)

# after each build, copy the assets from src/assets to build/assets so the assets
# can be found when running in a build tree
add_custom_command(TARGET coregaming POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/assets
        $<TARGET_FILE_DIR:coregaming>/assets
)

if (APPLE)
    set_target_properties(coregaming PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "CoreGaming")
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/assets/ DESTINATION CoreGaming.app/Contents/Resources)
    install(TARGETS coregaming BUNDLE DESTINATION .)
    install(CODE [[
        include(BundleUtilities)
        fixup_bundle("${CMAKE_INSTALL_PREFIX}/CoreGaming.app" "" "")
    ]])
elseif (UNIX)
    install(TARGETS coregaming RUNTIME DESTINATION usr/bin)
    install(TARGETS sfml-system sfml-window sfml-graphics sfml-audio LIBRARY DESTINATION usr/lib)
    # TODO: May eventually need to bring in assets from the build directory if they were changed by the build step
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/assets DESTINATION usr/share/coregaming)
elseif (WIN32)
    install(TARGETS coregaming RUNTIME DESTINATION .)
    install(FILES $<TARGET_RUNTIME_DLLS:coregaming> DESTINATION .)
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/assets/ DESTINATION assets)
endif ()

