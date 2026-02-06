#include <ranges>

#include <SFML/Window/Event.hpp>

#include <input.h>

Input::Input()
{
    for (auto & a : actionsList)
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
        case sf::Keyboard::Key::Space: this->setAsPressed(Action::Enter); break;
        case sf::Keyboard::Key::Up: this->setAsPressed(Action::MoveUp); break;
        case sf::Keyboard::Key::Down: this->setAsPressed(Action::MoveDown); break;
        case sf::Keyboard::Key::Left: this->setAsPressed(Action::MoveLeft); break;
        case sf::Keyboard::Key::Right: this->setAsPressed(Action::MoveRight); break;
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
    case Action::MoveUp:    return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
    case Action::MoveDown:  return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
    case Action::MoveLeft:  return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    case Action::MoveRight: return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
    case Action::ZoomIn: return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Add);
    case Action::ZoomOut: return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Subtract);
    default: return false;
    }
}
