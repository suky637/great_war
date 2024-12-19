#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <map>

class Component
{
    public:
    //Component();
    bool isClicked = false;
    sf::RenderWindow* win;
    sf::Vector2f position;
    sf::Vector2f size;
    bool visible = true;
    virtual void Input(sf::View* view);
    virtual bool isHovered(sf::View* view);
    virtual void Draw(sf::Font font);
    virtual std::string GetType();
    virtual Component* GetComponent();
    protected:
    Component() = default;
};