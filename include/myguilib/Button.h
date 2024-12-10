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

class Button: public Component
{
    private:
    sf::Text label;
    sf::RectangleShape rect{};
    bool lastClick = false;
    bool crntClicked = false;
    public:
    Button(sf::RenderWindow* win, GUI& gui, sf::Vector2f pos, sf::Vector2f size, std::string text, std::string id = "");
    void Input(sf::View* view) override;
    void Draw(sf::Font font) override;
    bool isHovered(sf::View* view) override;
    std::string GetType() override;
    Button* GetComponent();
};