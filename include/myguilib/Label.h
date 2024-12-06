#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "myguilib/Component.h"
#include "myguilib/GUI.h"

class Label: public Component
{
    private:
    sf::Text label;
    public:
    Label(sf::RenderWindow* win, GUI& gui, sf::Vector2f pos, int size, std::string text, std::string id = "");
    void Draw(sf::Font font) override;
};