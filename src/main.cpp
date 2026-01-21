#include "platform.h"
#include "game.h"

int main(int argc, char* argv[]) {
    Platform platform(800, 600, "SDL RPG");
    Game game(platform);
    platform.run([&](const float dt) { game.frame(dt); });
    return 0;
}
