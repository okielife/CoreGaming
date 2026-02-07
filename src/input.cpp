#include <ranges>

#include <SFML/Window/Event.hpp>

#include <input.h>

Input::Input()
{
    for (auto & a : actionsList)
    {
        pressed[a] = false;
    }
}

void Input::beginFrame() {
    anyPressed_ = false;
    for (auto& val : pressed | std::views::values) {
        val = false;
    }
}

void Input::setAsPressed(const Action a)
{
    pressed[a] = true;
}

void Input::update(const sf::Event& e) {
    if (e.type == sf::Event::KeyPressed) {  // && !e.key.repeat) {
        anyPressed_ = true;
        switch (e.key.code) {
        case sf::Keyboard::Key::Space: setAsPressed(Action::Enter); break;
        case sf::Keyboard::Key::Up: setAsPressed(Action::MoveUp); break;
        case sf::Keyboard::Key::Down: setAsPressed(Action::MoveDown); break;
        case sf::Keyboard::Key::Left: setAsPressed(Action::MoveLeft); break;
        case sf::Keyboard::Key::Right: setAsPressed(Action::MoveRight); break;
        case sf::Keyboard::Key::Escape: setAsPressed(Action::Quit); break;
        case sf::Keyboard::Key::Enter: setAsPressed(Action::Confirm); break;
        default: break;
        }
    }
}

bool Input::anyPressed() const {
    return anyPressed_;
}

bool Input::wasPressed(Action a) const {
    return pressed.at(a);
}

bool Input::isDown(const Action a) {
    switch (a) {
    case Action::MoveUp:    return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
    case Action::MoveDown:  return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
    case Action::MoveLeft:  return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    case Action::MoveRight: return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
    case Action::ZoomIn: return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Add);
    case Action::ZoomOut: return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Subtract);
    default: return false;
    }
}
