#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <map>
#include <vector>
#include <memory>

#include "engine/Scene.h"
#include "engine/Script.h"
#include "engine/EngineFunctions.h"
#include "scene_map.h"
#include "engine.h"
#include "mainmenu.h"

#include "language/gws.h"

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
    static Game instance;

    std::string save_file;
    json currentSave;

    std::string currentCountry;

    GWS gws;
    int currentScene = 0;
    int scroll;
    Game();
    Game(sf::RenderWindow* window);
    void ChangeScene(int scene);
    void Begin();
    void Update(float dt);
    void FixedUpdate();
    void Render();
    void Exit();
};