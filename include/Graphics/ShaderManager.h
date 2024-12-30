#include <SFML/Graphics.hpp>
#include <iostream>

class ShaderManager {

    public:
    static ShaderManager instance;
    ShaderManager();
    sf::Shader pixelShader;
};