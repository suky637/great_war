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

class DynLabel: public Component
{
    private:
    sf::Text label;
    public:
    DynLabel(sf::RenderWindow* win, GUI* gui, sf::Vector2f pos, int size, std::string text, std::string id = "", bool visible = true);
    void Draw(sf::Font font) override;
    void Value(std::string value);
    //bool isHovered(sf::View* view) override;
    std::string GetType() override;
    DynLabel* GetComponent() override;
};