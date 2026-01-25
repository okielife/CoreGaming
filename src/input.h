#pragma once

#include <array>
#include <bits/types.h>

#include "input.h"

union SDL_Event;

enum class Action {
    MoveUp,
    MoveDown,
    MoveLeft,
    MoveRight,
    ZoomIn,
    ZoomOut,
    Quit  // make sure Quit is the last one in this list
};
constexpr int ActionCount = static_cast<int>(Action::Quit) + 1;

class Input {
public:
    virtual ~Input() = default;
    void beginFrame();
    void update();
    void update(const SDL_Event& e);

    [[nodiscard]] bool anyPressed() const;
    [[nodiscard]] bool wasPressed(Action a) const;
    [[nodiscard]] bool isDown(Action a) const;
    void setAsPressed(Action a);

    const __uint8_t* keys_{nullptr};
    bool anyPressed_ = false;
    std::array<bool, ActionCount> pressed_{};
};
