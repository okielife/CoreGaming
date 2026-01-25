#include "input.h"

#include <SDL2/SDL.h>

void Input::beginFrame() {
    anyPressed_ = false;
    pressed_.fill(false);
}

void Input::setAsPressed(Action a)
{
    int const actionInt = static_cast<int>(a);
    pressed_[actionInt] = true;
}

void Input::update() {
    keys_ = SDL_GetKeyboardState(nullptr);
}

void Input::update(const SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && !e.key.repeat) {
        anyPressed_ = true;
        switch (e.key.keysym.scancode) {
        case SDL_SCANCODE_W: this->setAsPressed(Action::MoveUp); break;
        case SDL_SCANCODE_S: this->setAsPressed(Action::MoveDown); break;
        case SDL_SCANCODE_A: this->setAsPressed(Action::MoveLeft); break;
        case SDL_SCANCODE_D: this->setAsPressed(Action::MoveRight); break;
        case SDL_SCANCODE_KP_PLUS:  this->setAsPressed(Action::ZoomIn); break;
        case SDL_SCANCODE_KP_MINUS: this->setAsPressed(Action::ZoomOut); break;
        default: break;
        }
    }
}

bool Input::anyPressed() const {
    return anyPressed_;
}

bool Input::wasPressed(Action a) const {
    return pressed_[static_cast<int>(a)];
}

bool Input::isDown(const Action a) const {
    if (!keys_) return false;
    switch (a) {
    case Action::MoveUp:    return keys_[SDL_SCANCODE_W];
    case Action::MoveDown:  return keys_[SDL_SCANCODE_S];
    case Action::MoveLeft:  return keys_[SDL_SCANCODE_A];
    case Action::MoveRight: return keys_[SDL_SCANCODE_D];
    case Action::ZoomIn: return keys_[SDL_SCANCODE_KP_PLUS];
    case Action::ZoomOut: return keys_[SDL_SCANCODE_KP_MINUS];
    default: return false;
    }
}
