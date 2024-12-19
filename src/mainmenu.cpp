#include "mainmenu.h"

#include "gamelogic.h"

void MainMenu::Awake()
{
    std::fstream fgame{"ressources/game.json"};

    json game_json = json::parse(fgame);

    gui.window = window;
    gui.view = gui_view;
    gui.getDataByJSON(game_json.at("guis")[(int)(game_json["currentGUI"])], "mainmenu");
}

void MainMenu::Start()
{

}

void MainMenu::Update()
{
    gui.Update(&gui);

    if (gui.isClicked("Play"))
    {
        Game::instance.ChangeScene(1);
    }
    if (gui.isClicked("Quit"))
    {
        exit(0);
    }
}

void MainMenu::FixedUpdate()
{

}

void MainMenu::Draw()
{
    gui.Draw();
}