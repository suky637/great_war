#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <vector>
#include <memory>

#include "myguilib.h"

#define FixedDeltaTime (1 / 60)

class Script
{
    public:
    float deltaTime;
    int scroll;

    sf::RenderWindow* window;
    sf::View* view;
    
    virtual void Start();
    virtual void Update(GUI* gui);
    virtual void FixedUpdate();
    virtual void Draw();
    virtual std::string getId();
    virtual Script* getScript();
};