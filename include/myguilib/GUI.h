#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <utility>
#include <cstdarg>
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

#include "myguilib/Component.h"


class GUI
{
    public:
    bool createdGUI = false;
    sf::RenderTexture rendered_gui;
    float deltaTime;
    int scroll;

    sf::RenderWindow* window;
    sf::View* view;
    sf::Font font;
    bool hovered;
    bool Exist(std::string compId);
    void renderGUIImage();
    void Start();
    GUI();
    GUI(sf::Font& font);
    std::map<std::string, std::unique_ptr<Component>> components{};
    void Update(GUI* gui);
    void Draw();
    bool isClicked(std::string id);

    void getDataByJSON(std::string file, std::string prefix);
    std::string getId();
    GUI* getScript();

};