#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <vector>
#include <memory>
#undef GUI
#include "myguilib/GUI.h"

#define FixedDeltaTime (1 / 60)

class Scene
{
    public:
    GUI gui;
    sf::View* view;
    sf::View* gui_view;
    float deltaTime;
    sf::RenderWindow* window;
    std::string sceneName;
    int scroll;
    
    virtual void Awake() = 0;
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void FixedUpdate() = 0;
    virtual void Draw() = 0;
};