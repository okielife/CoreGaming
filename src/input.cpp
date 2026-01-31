#include "input.h"

#include <ranges>
#include <SFML/Window/Event.hpp>

Input::Input()
{
    for (auto & a : pressedActions)
    {
        this->pressed[a] = false;
    }
}

void Input::beginFrame() {
    this->anyPressed_ = false;
    for (auto& val : this->pressed | std::views::values) {
        val = false;
    }
}

void Input::setAsPressed(const Action a)
{
    this->pressed[a] = true;
}

void Input::update(const sf::Event& e) {
    if (e.type == sf::Event::KeyPressed) {  // && !e.key.repeat) {
        anyPressed_ = true;
        switch (e.key.code) {
        case sf::Keyboard::Key::Space: this->setAsPressed(Action::Sword); break;
        case sf::Keyboard::Key::Up: this->setAsPressed(Action::MenuUp); break;
        case sf::Keyboard::Key::Down: this->setAsPressed(Action::MenuDown); break;
        case sf::Keyboard::Key::Escape: this->setAsPressed(Action::Quit); break;
        case sf::Keyboard::Key::Enter: this->setAsPressed(Action::Confirm); break;
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
    case Action::MoveUp:    return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
    case Action::MoveDown:  return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
    case Action::MoveLeft:  return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    case Action::MoveRight: return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
    case Action::ZoomIn: return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Add);
    case Action::ZoomOut: return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Subtract);
    default: return false;
    }
}
