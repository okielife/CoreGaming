#include "platform/platform.h"
#include "game/game.h"

int main(int argc, char* argv[]) {
    Platform platform(800, 600, "SDL RPG");
    Game game(platform);
    platform.run([&](const float dt) {
        game.update(dt);
        game.render();
    });
    return 0;
}
