#include "engine/Mouse.h"

S_Mouse::S_Mouse() {
    for (int i = 0; i < 8; ++i) {
        this->mouseState[i] = false;
        this->lastMouseState[i] = false;
    }
}

void S_Mouse::UpdateInputs() {
    for (int i = 0; i < sf::Mouse::ButtonCount; ++i) {
        this->lastMouseState[i] = this->mouseState[i];
    }
}

void S_Mouse::SetMouseState(sf::Mouse::Button button) {
    this->mouseState[(int)button] = true;
}

void S_Mouse::SetMouseStateReleased(sf::Mouse::Button button) {
    this->mouseState[(int)button] = false;
}

bool S_Mouse::isMouseButtonDown(sf::Mouse::Button button) {
    return this->mouseState[(int)button] && !this->lastMouseState[(int)button];
}

bool S_Mouse::isMouseButtonUp(sf::Mouse::Button button) {
    return !this->mouseState[(int)button] && this->lastMouseState[(int)button];
}


S_Mouse S_Mouse::instance;