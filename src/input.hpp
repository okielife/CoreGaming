#pragma once

#include <array>
#include <unordered_map>

#include <SFML/Window/Event.hpp>

#include <input.hpp>

enum class Axis
{
    X,
    Y,
    Zoom
};

struct AxisState
{
    float raw = 0.f;
    bool engagedPositive = false;
    bool engagedNegative = false;
    bool pulsePositive = false;
    bool pulseNegative = false;
};

enum class AxisDirection
{
    Positive,
    Negative
};

enum class Action {
    Space,
    Confirm,
    Quit
};

struct Input {
    Input();
    void beginFrame();
    void handleEvent(const sf::Event& e);
    void update();

    [[nodiscard]] bool pressedThisFrame(Action a) const;
    [[nodiscard]] bool pressedThisFrame(Axis a, AxisDirection d) const;
    bool actionCurrentlyPressed(Action a) const;
    float axisCurrentValue(Axis a) const;
    int axisCurrentDigitalValue(Axis a) const;
    void setAsPressed(Action a);

    bool anyButtonPressedThisFrame = false;
    std::unordered_map<Action, bool> pressed{};

private:
    int joystickActiveID = -1;
    std::unordered_map<Axis, AxisState> axes;
};
