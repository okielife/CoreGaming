find_package(SDL2 CONFIG QUIET)
add_library(sdl INTERFACE)
target_link_libraries(sdl INTERFACE SDL2::SDL2 SDL2::SDL2main)
add_executable(game
        main.cpp
        engine/input.h
        engine/camera.h
        engine/renderer.h
        game/game.cpp
        game/game.h
        platform/audio.h
        platform/filesystem.h
        platform/platform.cpp
        platform/platform.h
        platform/sdl_input.cpp
        platform/sdl_input.h
        platform/sdl_renderer.cpp
        platform/sdl_renderer.h
)
target_link_libraries(game PRIVATE sdl)
