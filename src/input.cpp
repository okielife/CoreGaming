#include <cmath>
#include <ranges>

#include <SFML/Window/Event.hpp>

#include <input.hpp>
#include <iostream>
#include <ostream>

Input::Input()
{
    constexpr std::array actionsList = {
        Action::Space,
        Action::Confirm,
        Action::Quit
    };
    for (auto& a : actionsList)
    {
        pressed[a] = false;
    }
    constexpr std::array axisList = {
        Axis::X, Axis::Y, Axis::Zoom
    };
    for (auto & a: axisList)
    {
        axes[a] = {};
    }
    for (int i = 0; i < sf::Joystick::Count; ++i)
    {
        if (sf::Joystick::isConnected(i))
        {
            std::cout << "Found joystick on input " << i << std::endl;
            joystickActiveID = i;
            break;
        }
    }
}

void Input::beginFrame()
{
    if (joystickActiveID == -1)
    {
        for (int i = 0; i < sf::Joystick::Count; ++i)
        {
            if (sf::Joystick::isConnected(i))
            {
                std::cout << "Found joystick on input " << i << std::endl;
                joystickActiveID = i;
                break;
            }
        }
    }
    anyButtonPressedThisFrame = false;
    for (auto& val : pressed | std::views::values)
    {
        val = false;
    }
}

void Input::setAsPressed(const Action a)
{
    pressed[a] = true;
    anyButtonPressedThisFrame = true;
}

void Input::handleEvent(const sf::Event& e)
{
    if (e.type == sf::Event::KeyPressed)
    {
        switch (e.key.code)
        {
        case sf::Keyboard::Key::Space:
            setAsPressed(Action::Space);
            break;
        case sf::Keyboard::Key::Enter:
            setAsPressed(Action::Confirm);
            break;
        case sf::Keyboard::Key::Escape:
            setAsPressed(Action::Quit);
            break;
        default: break;
        }
    } else if (e.type == sf::Event::JoystickButtonPressed)
    {
        switch (e.joystickButton.button)
        {
        case 0:
            setAsPressed(Action::Confirm);
            break;
        case 1:
            setAsPressed(Action::Space);
            break;
        case 2:
            setAsPressed(Action::Quit);
            break;
        default:
            break;
        }
    }
}

void Input::update()
{
    constexpr float deadzone         = 0.15f;
    constexpr float engageThreshold  = 0.6f;
    constexpr float releaseThreshold = 0.3f;

    for (auto& [axis, state] : axes)
    {
        // clear last frame pulses
        state.pulsePositive = false;
        state.pulseNegative = false;

        float raw = 0.0f;

        if (joystickActiveID != -1)
        {
            switch (axis)
            {
            case Axis::X:
                raw = sf::Joystick::getAxisPosition(joystickActiveID, sf::Joystick::X) / 100.f;
                break;
            case Axis::Y:
                raw = sf::Joystick::getAxisPosition(joystickActiveID, sf::Joystick::Y) / 100.f;
                break;
            case Axis::Zoom:
                raw = sf::Joystick::getAxisPosition(joystickActiveID, sf::Joystick::PovY) / 100.f;
                break;
            default:
                break;
            }
        }

        // Deadzone
        if (std::abs(raw) < deadzone)
            raw = 0.f;

        state.raw = raw;

        // ==========================
        // POSITIVE SIDE
        // ==========================
        if (!state.engagedPositive)
        {
            if (raw >= engageThreshold)
            {
                state.engagedPositive = true;
                state.engagedNegative = false; // optional exclusivity
                state.pulsePositive = true;
            }
        }
        else if (raw <= releaseThreshold)
        {
            state.engagedPositive = false;
        }

        // ==========================
        // NEGATIVE SIDE
        // ==========================
        if (!state.engagedNegative)
        {
            if (raw <= -engageThreshold)
            {
                state.engagedNegative = true;
                state.engagedPositive = false; // optional exclusivity
                state.pulseNegative = true;
            }
        }
        else if (raw >= -releaseThreshold)
        {
            state.engagedNegative = false;
        }
    }
}

bool Input::pressedThisFrame(Action const a) const
{
    return pressed.at(a);
}

bool Input::pressedThisFrame(Axis const a, AxisDirection const d) const
{
    auto & currentState = axes.at(a);
    switch (d)
    {
    case AxisDirection::Positive:
        return currentState.pulsePositive;
    case AxisDirection::Negative:
        return currentState.pulseNegative;
    }
    return false;
}

float Input::axisCurrentValue(Axis const a) const
{
    if (joystickActiveID >= 0)
    {
        switch (a)
        {
        case Axis::X:
            return sf::Joystick::getAxisPosition(joystickActiveID, sf::Joystick::X) / 100.f;
        case Axis::Y:
            return sf::Joystick::getAxisPosition(joystickActiveID, sf::Joystick::Y) / 100.f;
        case Axis::Zoom:
            return sf::Joystick::getAxisPosition(joystickActiveID, sf::Joystick::PovY) / 100.f;
        }
    } else{
        switch (a)
        {
        case Axis::X:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                return -1.0f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                return 1.0f;
        case Axis::Y:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                return -1.0f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                return 1.0f;
        case Axis::Zoom:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
                return -1.0f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
                return 1.0;
        }
    }
    return 0.0;
}

bool Input::actionCurrentlyPressed(const Action a) const
{
    if (joystickActiveID >= 0)
    {
        switch (a)
        {
        case Action::Confirm:
            return sf::Joystick::isButtonPressed(joystickActiveID, 0);
        case Action::Space:
            return sf::Joystick::isButtonPressed(joystickActiveID, 1);
        case Action::Quit:
            return sf::Joystick::isButtonPressed(joystickActiveID, 2);
        }
    } else
    {
        switch (a)
        {
        case Action::Space:
            return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
        case Action::Confirm:
            return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter);
        case Action::Quit:
            return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);
        default:
            return false;
        }
    }
    return false;
}
