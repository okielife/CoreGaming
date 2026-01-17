#pragma once

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
    [[nodiscard]] virtual bool isDown(Action a) const = 0;
};
