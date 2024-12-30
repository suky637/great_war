#include <SFML/Graphics.hpp>

class S_Keyboard {
    private:
    bool keyboardState[128];
    bool lastKeyboardState[128];

    public:
    S_Keyboard();
    static S_Keyboard instance;
    void UpdateInputs();
    void SetKeyboardState(sf::Keyboard::Key key);
    void SetKeyboardStateReleased(sf::Keyboard::Key key);
    bool isKeyDown(sf::Keyboard::Key key);
    bool isKeyUp(sf::Keyboard::Key key);
};