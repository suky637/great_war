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


class GUI
{
    public:
    float deltaTime;
    int scroll;

    sf::RenderWindow* window;
    sf::View* view;
    sf::Font font;
    bool hovered;
    GUI();
    GUI(sf::Font& font);
    std::map<std::string, std::unique_ptr<Component>> components{};
    void Update(GUI* gui);
    void Draw();
    bool isClicked(std::string id);
    std::string getId();
    GUI* getScript();

};