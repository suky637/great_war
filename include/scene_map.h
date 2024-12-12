#pragma once
#include "engine.h"
#include "myguilib.h"
#include "Physics/PIP.h"

using json = nlohmann::json;

class Europe: public Scene
{
    private:

    // GameObjects
    sf::RectangleShape referenceImageForEditor;
    sf::Texture europeReferenceMap;

    std::vector<std::pair<sf::Text, sf::CircleShape>> points{};
    sf::ConvexShape preview;

    sf::RectangleShape background;

    std::string currentCountry = "";

    // Rest
    bool hide_placeholder = false;
    std::vector<std::pair<sf::ConvexShape, sf::Text>> shapes{};
    std::vector<std::unique_ptr<Script>> scripts;
    std::map<std::string, std::string> isos{};
    sf::Font font;
    json data;
    json game_json;

    int preview_index = 0;

    GUI gui;

    public:
    std::string sceneName;
    Europe();
    void Start() override;
    void Update() override;
    void FixedUpdate() override;
    void Draw() override;
    void ReadGUIJson();
    void Editor(bool gui_hovered);
};
