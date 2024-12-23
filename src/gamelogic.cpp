#include "gamelogic.h"
#include "choose_save.h"
#include "engine/colour.h"

Game::Game(sf::RenderWindow* window)
{
    this->win = window;
}

Game::Game()
{

}

void Game::AdjustViewport()
{
    uint32_t width = win->getSize().x;
    uint32_t height = win->getSize().y;

    uint32_t desired_width = height / 9 * 16;
    uint32_t desired_height = width / 16 * 9;
    
    float ratio_width = (float)(desired_width) / (float)(width);
    float ratio_height = (float)(desired_height) / (float)(height);

    if (ratio_width < 1.f)
    {
        viewport.setViewport(sf::FloatRect((1.f - ratio_width) / 2.f, 0.f, ratio_width, 1.f));
        gui_viewport.setViewport(sf::FloatRect((1.f - ratio_width) / 2.f, 0.f, ratio_width, 1.f));
    }
    else
    {
        viewport.setViewport(sf::FloatRect(0.f, (1.f - ratio_height) / 2.f, 1.f, ratio_height));
        gui_viewport.setViewport(sf::FloatRect((1.f - ratio_width) / 2.f, 0.f, ratio_width, 1.f));
    }
}

void Game::Begin()
{
    std::fstream f{"ressources/window.json"};
    json data = json::parse(f);

    std::string title = data["window_name"];
    win->setTitle(title);
    win->setSize(sf::Vector2u(data["default_width"], data["default_height"]));
    sf::Texture tex;
    tex.loadFromFile(data["icon"]);
    unsigned char* pixels = new unsigned char[tex.getSize().x * tex.getSize().y * 4];
    tex.update(pixels, 0, 0, tex.getSize().x, tex.getSize().y);
    win->setIcon(tex.getSize().x, tex.getSize().y, pixels);
    defaultWindow = win->getView();
    viewport = win->getView();
    gui_viewport = win->getView();

    gws.interpret(data["links"][0]);

    MainMenu mainMenu{};
    mainMenu.window = win;
    mainMenu.view = &viewport;
    mainMenu.gui_view = &gui_viewport;
    mainMenu.Awake();
    scenes.push_back(std::make_unique<MainMenu>(std::move(mainMenu)));

    ChooseSave chooseSave{};
    chooseSave.window = win;
    chooseSave.view = &viewport;
    chooseSave.gui_view = &gui_viewport;
    chooseSave.Awake();
    scenes.push_back(std::make_unique<ChooseSave>(std::move(chooseSave)));

    Europe europe{};
    europe.window = win;
    europe.view = &viewport;
    europe.gui_view = &gui_viewport;
    europe.Awake();
    scenes.push_back(std::make_unique<Europe>(std::move(europe)));

    scenes[currentScene]->Start();
    gws.runEvent(std::to_string(currentScene), GWS_EventTypes::START, &scenes[currentScene]->gui);
}

void Game::Update(float dt)
{
    scenes[currentScene]->scroll = scroll;
    scenes[currentScene]->deltaTime = dt;
    scenes[currentScene]->Update();
    gws.runEvent(std::to_string(currentScene), GWS_EventTypes::UPDATE, &scenes[currentScene]->gui);


    sf::Vector2f mouseCoord = win->mapPixelToCoords(sf::Mouse::getPosition(*win), viewport);
}

void Game::FixedUpdate()
{
    AdjustViewport();
    scenes[currentScene]->FixedUpdate();
    gws.runEvent(std::to_string(currentScene), GWS_EventTypes::FIXED_UPDATE, &scenes[currentScene]->gui);
}


void Game::Render()
{
    win->setView(defaultWindow);
    win->clear(sf::Color::Black);

    win->setView(viewport);

    scenes[currentScene]->Draw();
}

void Game::ChangeScene(int scene)
{
    currentScene = scene;
    scenes[currentScene]->Start();
    gws.runEvent(std::to_string(currentScene), GWS_EventTypes::START, &scenes[currentScene]->gui);
}

void Game::Exit() {
    // Saving happens here
    if (this->save_file != "") {
        std::string s = this->currentSave.dump();

        std::ofstream __file(this->save_file, std::ios::out);
        __file << s;
        __file.close();

        std::cout << "Wrote data sucessfuly to " << TEXT_GREEN << this->save_file << RESET_COLOR << "\n";
    }

    exit(0);
}

Game Game::instance;