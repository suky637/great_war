#include <SFML/Graphics.hpp>

class S_Mouse {
    private:
    bool mouseState[8];
    bool lastMouseState[8];

    public:
    S_Mouse();
    static S_Mouse instance;
    void UpdateInputs();
    void SetMouseState(sf::Mouse::Button button);
    void SetMouseStateReleased(sf::Mouse::Button button);
    bool isMouseButtonDown(sf::Mouse::Button button);
    bool isMouseButtonUp(sf::Mouse::Button button);
};