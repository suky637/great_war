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

class DynImageBox: public Component
{
    private:
    sf::Texture texture;
    sf::RectangleShape rect;
    public:
    std::string path;
    DynImageBox(sf::RenderWindow* win, GUI& gui, sf::Vector2f pos, sf::Vector2f size, std::string _path, std::string id = "", bool visible = true);
    void Draw(sf::Font font) override;
    void Value(std::string path);
    std::string GetType() override;
    DynImageBox* GetComponent() override;
};