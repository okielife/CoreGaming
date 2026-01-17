#pragma once
#include <SDL.h>
#include "../engine/input.h"

class SDLInput : public Input {
public:
    void update();
    [[nodiscard]] bool isDown(Action a) const override;

private:
    const Uint8* keys_{nullptr};
};
