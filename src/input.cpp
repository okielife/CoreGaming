#include "input.h"

void Input::update() {
    keys_ = SDL_GetKeyboardState(nullptr);
}

bool Input::isDown(const Action a) const {
    if (!keys_) return false;

    switch (a) {
    case Action::MoveUp:    return keys_[SDL_SCANCODE_W];
    case Action::MoveDown:  return keys_[SDL_SCANCODE_S];
    case Action::MoveLeft:  return keys_[SDL_SCANCODE_A];
    case Action::MoveRight: return keys_[SDL_SCANCODE_D];
    default: return false;
    }
}
