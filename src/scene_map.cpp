#include "scene_map.h"

// scripts includes
#include "camera_movement.h"
#include "scripts/countryManager.h"

void Europe::Awake()
{
    sceneName = "europe";
    // Loading ressources
    std::fstream fgame{"ressources/game.json"};

    game_json = json::parse(fgame);

    std::fstream f{game_json.at("worlds")[(int)(game_json["currentWorld"])]};

    data = json::parse(f);

    currentCountry = "NONE";


    // Loading every countries
    for (auto country : data.at("countries"))
    {
        isos.insert_or_assign(country["ISO"], country["name"]);
        std::cout << "Detected a country!, " << country.at("name") << "\n";
        for (auto region : country.at("regions"))
        {
            sf::ConvexShape shape{};
            shape.setOutlineColor(sf::Color::Black);
            shape.setOutlineThickness(0.1f);
            shape.setFillColor(sf::Color(country.at("colour")["R"], country.at("colour")["G"], country.at("colour")["B"], data["config"]["countryOpacity"]));
            int index = 0;
            for (auto coord : region.at("coords"))
            {
                sf::Vector2f vec2;
                vec2.x = coord["X"];
                vec2.y = coord["Y"];
                shape.setPointCount(index+1);
                shape.setPoint(index, vec2);
                index++;
            }
            sf::Text txt;
            std::string reg_name = region["name"];
            txt.setScale(sf::Vector2f(region["scale"], region["scale"]));
            txt.setString(reg_name);
            txt.setPosition(sf::Vector2f(region["text_pos"]["X"], region["text_pos"]["Y"]));
            

            this->shapes.push_back(std::pair<sf::ConvexShape, sf::Text>(shape, txt));
        }
    }

    if (data["config"]["EDITOR_SNAPPING_ENABLED"])
    {
        std::cout << "WARNING: Snapping may cause some performance issues.\n";
    }

    CameraMovement cameraMovement{};
    cameraMovement.view = view;
    cameraMovement.Start();
    scripts.insert_or_assign("1", std::make_unique<CameraMovement>(std::move(cameraMovement)));

    europeReferenceMap.loadFromFile("ressources/image.png");
    referenceImageForEditor.setSize(sf::Vector2f(1280, 720));
    referenceImageForEditor.setTexture(&europeReferenceMap);

    preview.setFillColor(sf::Color(0, 255, 0, 100));
    
    gui.window = window;
    gui.view = gui_view;
    gui.getDataByJSON(game_json.at("guis")[(int)(game_json["currentGUI"])], "world_map_gui");

    background.setFillColor(sf::Color(data["config"]["backgroundColour"]["R"], data["config"]["backgroundColour"]["G"], data["config"]["backgroundColour"]["B"], data["config"]["backgroundColour"]["A"]));
    background.setSize(sf::Vector2f(1280, 720));

    CountryManager countryManager{};
    countryManager.view = view;
    countryManager.window = window;
    countryManager.Start();
    scripts.insert_or_assign("countryManager", std::make_unique<CountryManager>(std::move(countryManager)));
}

void Europe::Start()
{

}

void Europe::Editor(bool gui_hovered)
{
    if (data["config"]["EDITOR_MODE"] == false) return;
    static bool lastFocus = false;
    bool crntFocus = window->hasFocus();

    sf::Vector2i mousePosPix = sf::Mouse::getPosition(*window);
    sf::Vector2f mousePos = window->mapPixelToCoords(mousePosPix, *view);
    static bool lastClick = false;
    static bool firstClick = false;
    static bool impossible = false;
    bool crntClick = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    if (!firstClick && crntClick)
    {
        if (gui_hovered || mousePosPix.y < 0 || (!lastFocus && crntFocus) || !crntFocus)
        {
            impossible = true;
        }
    }

    firstClick = crntClick;

    if (lastClick && !crntClick)
    {
        if (gui_hovered || mousePosPix.y < 0 || (!lastFocus && crntFocus) || !crntFocus)
            impossible = true;
        if (impossible)
            impossible = false;
        else
        {
            sf::CircleShape circle;
            circle.setFillColor(sf::Color::Red);
            // adding snapping (optionnal)
            if (data["config"]["EDITOR_SNAPPING_ENABLED"])
            {
                sf::Vector2f pointA = mousePos;
                for (const auto& shape : shapes)
                {
                    for (int i = 0; i < shape.first.getPointCount(); ++i)
                    {
                        sf::Vector2f pointB = shape.first.getPoint(i);
                        float distance = sqrt((pointA.x-pointB.x)*(pointA.x-pointB.x) + (pointA.y-pointB.y)*(pointA.y-pointB.y));
                        if (distance <= data["config"]["EDITOR_SNAPPING"])
                        {
                            mousePos = pointB;
                            circle.setFillColor(sf::Color::Yellow);
                            break;
                        }
                    }
                }
            }

            // On Release
            circle.setRadius(3);
            // Getting Mouse Position
            
            circle.setPosition(mousePos - sf::Vector2f(1.5f, 1.5f));

            // Creating text
            sf::Text text;
            text.setString("(" + std::to_string(mousePos.x) + "; " + std::to_string(mousePos.y) + ")");
            text.setFillColor(sf::Color::White);
            text.setCharacterSize(12);
            text.setScale(sf::Vector2f(0.2f, 0.2f));
            text.setPosition(mousePos);

            // Adding to the array
            points.push_back(std::pair<sf::Text, sf::CircleShape>(text, circle));
            preview.setPointCount(preview_index+1);
            preview.setPoint(preview_index, mousePos);
            preview_index++;
        }
    }
    lastFocus = crntFocus;
    lastClick = crntClick;
}

void Europe::Update()
{
    static bool lastFocus = false;
    bool crntFocus = window->hasFocus();

    gui.Update(&gui);

    if (gui.isClicked("Create Code"))
    {
        std::cout << "GENERATED COORDINATES: \n";
        for (auto point : points)
        {
            std::cout << "{\"X\": " << point.first.getPosition().x << ", \"Y\": " << point.first.getPosition().y << "},\n";
        }
    }
    else if (gui.isClicked("Clear"))
    {
        preview.setPointCount(0);
        preview_index = 0;
        points.clear();
    }
    

    for (const auto& [k, script] : scripts)
    {
        if (!((!lastFocus && crntFocus) || !crntFocus)) {
            script->scroll = scroll;
            script->deltaTime = deltaTime;
            script->Update(&gui);
        }
    }

    if (!((!lastFocus && crntFocus) || !crntFocus))
    {
        static bool lastH = false;
        bool crntH = sf::Keyboard::isKeyPressed(sf::Keyboard::H);

        if (!lastH && crntH) hide_placeholder = !hide_placeholder;

        lastH = crntH;

        this->Editor(gui.hovered);

        // just testing something
        for (auto shape : shapes)
        {
            if (Physics::PIP_Collision(shape.first, window->mapPixelToCoords(sf::Mouse::getPosition(*window), *view)) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                // Getting the country from ISO code
                std::string iso = shape.second.getString().toAnsiString().substr(0, shape.second.getString().toAnsiString().find_first_of('_'));
                CountryManager* man = (CountryManager*)scripts.at("countryManager")->getScript();
                man->selectedCountry = iso;
            }
        }
    }
    lastFocus = crntFocus;
}

void Europe::FixedUpdate()
{
    for (const auto& [k, script] : scripts)
    {
        script->FixedUpdate();
    }
}

void Europe::Draw()
{
    this->window->draw(background);

    if (!hide_placeholder)
    {
        referenceImageForEditor.setTexture(&europeReferenceMap);
        this->window->draw(referenceImageForEditor);
    }
    for (auto shape : shapes)
    {
        this->window->draw(shape.first);
        shape.second.setFont(font);
        this->window->draw(shape.second);
    }
    if (preview.getPointCount() >= 3)
        this->window->draw(preview);
    for (auto point : points)
    {
        this->window->draw(point.second);
        point.first.setFont(font);
        this->window->draw(point.first);
    }
    //window->draw(test);
    for (const auto& [k, script] : scripts)
    {
        script->Draw();
    }
    gui.Draw();
}