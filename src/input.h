#pragma once

#include <array>
#include <unordered_map>

#include <SFML/Window/Event.hpp>

#include <input.h>

enum class Action {
    MoveUp,
    MoveDown,
    MoveLeft,
    MoveRight,
    Enter,
    ZoomIn,
    ZoomOut,
    Confirm,
    Quit
};

constexpr std::array actionsList = {
    Action::MoveUp,
    Action::MoveDown,
    Action::MoveLeft,
    Action::MoveRight,
    Action::Enter,
    Action::ZoomIn,
    Action::ZoomOut,
    Action::Quit,
    Action::Confirm
};

struct Input {
    Input();
    void beginFrame();
    void update(const sf::Event& e);

    [[nodiscard]] bool anyPressed() const;
    [[nodiscard]] bool wasPressed(Action a) const;
    static bool isDown(Action a) ;
    void setAsPressed(Action a);

    bool anyPressed_ = false;
    std::unordered_map<Action, bool> pressed{};
};
