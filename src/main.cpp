#include <platform.hpp>
#include <game.hpp>

int main() {
    Platform platform;
    Game game(platform.input_, platform.audio_);
    platform.run(game);
    return 0;
}
