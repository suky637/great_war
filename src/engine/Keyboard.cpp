#include "engine/Keyboard.h"

S_Keyboard::S_Keyboard() {
    for (int i = 0; i < 128; ++i) {
        this->keyboardState[i] = false;
        this->lastKeyboardState[i] = false;
    }
}

void S_Keyboard::UpdateInputs() {
    for (int i = 0; i < sf::Keyboard::KeyCount; ++i) {
        this->lastKeyboardState[i] = this->keyboardState[i];
    }
}

void S_Keyboard::SetKeyboardState(sf::Keyboard::Key key) {
    this->keyboardState[(int)key] = true;
}

void S_Keyboard::SetKeyboardStateReleased(sf::Keyboard::Key key) {
    this->keyboardState[(int)key] = false;
}

bool S_Keyboard::isKeyDown(sf::Keyboard::Key key) {
    return this->keyboardState[(int)key] && !this->lastKeyboardState[(int)key];
}

bool S_Keyboard::isKeyUp(sf::Keyboard::Key key) {
    return !this->keyboardState[(int)key] && this->lastKeyboardState[(int)key];
}

S_Keyboard S_Keyboard::instance;