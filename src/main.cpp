#include <platform.h>
#include <game.h>

int main() {
    Platform platform;
    Game game(platform.input_, platform.audio_);
    platform.run(game);
    return 0;
}
