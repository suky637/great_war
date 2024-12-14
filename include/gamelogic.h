#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <map>
#include <memory>

#include "engine.h"
#include "scene_map.h"
#include "engine.h"
#include "mainmenu.h"

using json = nlohmann::json;

class Game
{
    private:
    sf::RenderWindow* win;
    sf::View viewport;
    sf::View gui_viewport;
    sf::View defaultWindow;
    std::vector<std::unique_ptr<Scene>> scenes{};

    void AdjustViewport();

    public:
    int currentScene = 0;
    int scroll;
    Game(sf::RenderWindow* window);
    void Begin();
    void Update(float dt);
    void FixedUpdate();
    void Render();
};