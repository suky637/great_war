#include "settings_scene.h"

void Settings_Scene::Awake() {
    std::fstream fgame{"ressources/game.json"};

    json game_json = json::parse(fgame);

    gui.window = window;
    gui.view = gui_view;
    gui.getDataByJSON(game_json.at("guis")[(int)(game_json["currentGUI"])], "settings");
}

void Settings_Scene::Start() {

}

void Settings_Scene::Update() {
    gui.Update(&gui);

    if (gui.isClicked("set_english")) {
        std::fstream fgame{"ressources/game.json"};

        json game_json = json::parse(fgame);

        game_json["currentLanguage"] = "English";

        std::string s = game_json.dump();

        std::ofstream __file("ressources/game.json", std::ios::out);
        __file << s;
        __file.close();
    }
    if (gui.isClicked("set_french")) {
        std::fstream fgame{"ressources/game.json"};

        json game_json = json::parse(fgame);

        game_json["currentLanguage"] = "Français";

        std::string s = game_json.dump();

        std::ofstream __file("ressources/game.json", std::ios::out);
        __file << s;
        __file.close();
    }
}

void Settings_Scene::FixedUpdate() {

}

void Settings_Scene::Draw() {
    gui.Draw();
}

Settings_Scene Settings_Scene::instance;