#pragma once
#include "engine.h"
#include "myguilib.h"
#include "Physics/PIP.h"

using json = nlohmann::json;

struct Country {
    sf::ConvexShape shape;
    std::string owner;
    std::string region_name;
    sf::Text text;
    sf::Sprite render_shape;
    sf::Texture render_texture;
};

class Europe: public Scene
{
    private:

    // GameObjects
    sf::RectangleShape referenceImageForEditor;
    sf::Texture europeReferenceMap;

    std::vector<std::pair<sf::Text, sf::CircleShape>> points{};
    std::map<std::string, sf::Color> colours_iso{};
    sf::ConvexShape preview;


    sf::Sprite troop_render_batch_sprite;
    sf::Sprite render_batch_sprite;

    std::string currentCountry = "";

    // Rest
    bool hide_placeholder = false;
    std::map<std::string, std::unique_ptr<Script>> scripts;
    sf::Font font;
    json data;
    json game_json;

    int preview_index = 0;

    std::pair<sf::Sprite, sf::Texture> pixelizeShape(sf::ConvexShape& shape, float pixelSize, sf::Color shapeColour);
    std::map<std::string, sf::CircleShape> troopsRender{};
    json adjacentPolygons{};
    std::map<std::string, std::string> region_to_iso{};

    public:
    sf::RenderTexture troop_render_batch;
    sf::RenderTexture render_batch;
    sf::RectangleShape background;

    /*
     ██████╗██╗     ██╗███████╗███╗   ██╗████████╗     ██████╗ ██╗      ██████╗ ██████╗  █████╗ ██╗     ███████╗
    ██╔════╝██║     ██║██╔════╝████╗  ██║╚══██╔══╝    ██╔════╝ ██║     ██╔═══██╗██╔══██╗██╔══██╗██║     ██╔════╝
    ██║     ██║     ██║█████╗  ██╔██╗ ██║   ██║       ██║  ███╗██║     ██║   ██║██████╔╝███████║██║     ███████╗
    ██║     ██║     ██║██╔══╝  ██║╚██╗██║   ██║       ██║   ██║██║     ██║   ██║██╔══██╗██╔══██║██║     ╚════██║
    ╚██████╗███████╗██║███████╗██║ ╚████║   ██║       ╚██████╔╝███████╗╚██████╔╝██████╔╝██║  ██║███████╗███████║
    ╚═════╝╚══════╝╚═╝╚══════╝╚═╝  ╚═══╝   ╚═╝        ╚═════╝ ╚══════╝ ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝
    */

    int client_money = 10;
    int client_stability = 60;


    /*
    ██████╗ ███████╗███████╗████████╗
    ██╔══██╗██╔════╝██╔════╝╚══██╔══╝
    ██████╔╝█████╗  ███████╗   ██║   
    ██╔══██╗██╔══╝  ╚════██║   ██║   
    ██║  ██║███████╗███████║   ██║   
    ╚═╝  ╚═╝╚══════╝╚══════╝   ╚═╝  
    */

    void CreateTroopBatch();
    std::vector<Country> shapes{};
    std::map<std::string, std::string> isos{};
    std::string sceneName;
    static Europe instance;
    Europe() = default;
    void Awake() override;
    void Start() override;
    void Update() override;
    void FixedUpdate() override;
    void Draw() override;
    void Editor(bool gui_hovered);
    void RenderBatch(bool dontClear = false);
    void ClearBatch();
    void CreateAdjacentTerritories();
};
