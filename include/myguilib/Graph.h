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

class Graph: public Component
{
    private:
    sf::RectangleShape rect;
    GUI* gui;
    public:
    std::vector<float> points{};
    float precision = 1.f;
    Graph(sf::RenderWindow* win, GUI* gui, sf::Vector2f pos, sf::Vector2f size, std::string id = "", bool visible = true);
    void Draw(sf::Font font) override;
    bool isHovered(sf::View* view) override;
    void addPoint(float y);
    std::string GetType() override;
    Graph* GetComponent() override;
};