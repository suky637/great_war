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

class ImageBox: public Component
{
    private:
    sf::Texture texture;
    sf::RectangleShape rect;
    public:
    ImageBox(sf::RenderWindow* win, GUI& gui, sf::Vector2f pos, sf::Vector2f size, std::string _path, std::string id = "", bool visible = true);
    void Draw(sf::Font font) override;
    std::string GetType() override;
    ImageBox* GetComponent() override;
};