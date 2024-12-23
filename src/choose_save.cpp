#include "choose_save.h"
#include <filesystem>
#include "gamelogic.h"

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
        save["money"] = "1";
        save["stability"] = "100";
    }
    else {
        Game::instance.currentCountry = save["country"];
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