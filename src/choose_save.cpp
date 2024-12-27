#include "choose_save.h"
#include <filesystem>
#include "gamelogic.h"
#include "scene_map.h"
#include "engine/colour.h"

#define saves 2

void ChooseSave::createData() {
    for (int i = 0; i < saves; i++) {
        if (!std::filesystem::exists(std::filesystem::relative("ressources/data/save_" + std::to_string(i) + ".json"))) {
            std::ofstream outFile("ressources/data/save_" + std::to_string(i) + ".json");
            outFile << "{\"reset\": true}";
            outFile.close();
        }
    }

    for (int i = 0; i < saves; i++) {
        std::fstream f_save{"ressources/data/save_" + std::to_string(i) + ".json"};
        json temp = json::parse(f_save);
        if (temp["reset"] == false) {
            std::string id = "save_" + std::to_string(i) + "_flag";
            DynImageBox* flag_to_change = (DynImageBox*)gui.components[id]->GetComponent();
            flag_to_change->Value("ressources/flags/" + std::string(temp["country"]) + ".png");
        }
        else {
            std::string id = "save_" + std::to_string(i) + "_flag";
            DynImageBox* flag_to_change = (DynImageBox*)gui.components[id]->GetComponent();
            flag_to_change->Value("ressources/flags/NONE.png");
        }
        f_save.close();
    }
}

void ChooseSave::Awake() {
    std::fstream fgame{"ressources/game.json"};

    json game_json = json::parse(fgame);

    gui.window = window;
    gui.view = gui_view;
    gui.getDataByJSON(game_json.at("guis")[(int)(game_json["currentGUI"])], "selectSave");

    this->createData();

    fgame.close();
}

void ChooseSave::Start() {
}

void ChooseSave::loadData() {
    #define save Game::instance.currentSave
    if (save["reset"] == true) {
        save["reset"] = false;
        save["country"] = "NONE";
        save["countries"] = json::object();
        std::cout << "(choose_save.cpp / line 58) Europe's ISOs = " << Europe::instance.isos.size() << "\n";
        for (const auto& [k, v] : Europe::instance.isos) {
            json item = {
                {"money", 10},
                {"stability", 60},
                {"territories", json::array()}
            };
            // Horrible but works
            for (const auto& region : Europe::instance.shapes) {
                if (k == region.owner) {
                    item["territories"].push_back(region.region_name);
                }
            }
            save["countries"][k] = item;
        }
    }
    else {
        Game::instance.currentCountry = save["country"];
        /*
            Loading country data
        */

        // Goodluck fixing performance issues later for loading data
        for (auto& country : save["countries"].items()) {
            for (auto& territory : country.value().at("territories")) {
                for (int i = 0; i < Europe::instance.shapes.size(); ++i) {
                    if (Europe::instance.shapes[i].region_name == territory) {
                        Europe::instance.shapes[i].owner = country.key();
                    }
                }
            }
        }

        /*
            Loading client side stuff
        */
        if (save["country"] != "NONE") {
            Europe::instance.client_money = save["countries"][save["country"]]["money"];
            Europe::instance.client_stability = save["countries"][save["country"]]["stability"];
        }
    }
}

void ChooseSave::Update() {
    // TODO: Change this later when updating to an infinite saving system
    gui.Update(&gui);
    if (gui.isClicked("save_I_play")) {
        std::fstream f_save{"ressources/data/save_0.json"};
        Game::instance.currentSave = json::parse(f_save);
        Game::instance.save_file = "ressources/data/save_0.json";
        f_save.close();
        this->loadData();
    }
    else if (gui.isClicked("save_II_play")) {
        std::fstream f_save{"ressources/data/save_1.json"};
        Game::instance.currentSave = json::parse(f_save);
        Game::instance.save_file = "ressources/data/save_1.json";
        f_save.close();
        this->loadData();
    }

    if (gui.isClicked("save_I_reset")) {
        std::filesystem::remove(std::filesystem::relative("ressources/data/save_0.json"));
        this->createData();
    }
    else if (gui.isClicked("save_II_reset")) {
        std::filesystem::remove(std::filesystem::relative("ressources/data/save_1.json"));
        this->createData();
    }
}

void ChooseSave::FixedUpdate() {

}

void ChooseSave::Draw() {
    gui.Draw();
}

ChooseSave ChooseSave::instance;