#include "constants.h"
#include "platform.h"
#include "game.h"

int main(int argc, char* argv[]) {
    Platform platform(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    Game game(platform.renderer_, platform.input_, platform.audio_);
    platform.run(game);
    return 0;
}
