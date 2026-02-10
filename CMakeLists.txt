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

if (APPLE)
    set_target_properties(game PROPERTIES
            MACOSX_BUNDLE_BUNDLE_NAME "CoreGaming"
    )
    install(
            DIRECTORY ${CMAKE_SOURCE_DIR}/src/assets
            DESTINATION CoreGaming.app/Contents/Resources
    )
    include(BundleUtilities)
    install(TARGETS game BUNDLE DESTINATION .
    )
    install(CODE [[
        include(BundleUtilities)
        fixup_bundle(
            "${CMAKE_INSTALL_PREFIX}/CoreGaming.app"
            ""
            ""
        )
    ]])
elseif (UNIX)  # AND NOT APPLE
    install(TARGETS game RUNTIME DESTINATION usr/bin)
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/assets DESTINATION .)
    # Define the content you want to write
    set(FILE_CONTENT [=[
"#!/bin/sh
HERE="$(dirname "$(readlink -f "$0")")"
export LD_LIBRARY_PATH="$HERE/usr/lib:$LD_LIBRARY_PATH"
exec "$HERE/usr/bin/game" "$@"
]=]
    )
    set(OUTPUT_FILE "${CMAKE_BINARY_DIR}/cmake/AppRun.in")
    file(WRITE "${OUTPUT_FILE}" "${FILE_CONTENT}")
    install(PROGRAMS
            ${CMAKE_SOURCE_DIR}/cmake/AppRun.in
            DESTINATION .
            RENAME AppRun
    )
elseif (WIN32)
    install(TARGETS game RUNTIME DESTINATION .)
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/assets DESTINATION assets)
    include(InstallRequiredSystemLibraries)

    set(CPACK_PACKAGE_NAME "CoreGaming")
    set(CPACK_PACKAGE_VENDOR "Name")
    set(CPACK_PACKAGE_VERSION "1.0.0")

    set(CPACK_PACKAGE_INSTALL_DIRECTORY "CoreGaming")

    set(CPACK_NSIS_DISPLAY_NAME "CoreGaming")
    set(CPACK_NSIS_PACKAGE_NAME "CoreGaming")
    set(CPACK_NSIS_CONTACT "notlee@notlee.notlee")

    set(CPACK_NSIS_MODIFY_PATH OFF)
    set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)

    set(CPACK_GENERATOR "NSIS")

    include(CPack)
    set(CPACK_NSIS_CREATE_ICONS_EXTRA "${CPACK_NSIS_CREATE_ICONS_EXTRA} CreateShortCut '$DESKTOP\\\\MyGame.lnk' '$INSTDIR\\\\game.exe'")
endif ()
