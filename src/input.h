#pragma once

#include <SDL.h>
#include "input.h"

enum class Action {
    MoveUp,
    MoveDown,
    MoveLeft,
    MoveRight,
    Quit
};

class Input {
public:
    virtual ~Input() = default;
    void update();
    [[nodiscard]] bool isDown(Action a) const;
    const Uint8* keys_{nullptr};
};
