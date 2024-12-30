#include "scene_map.h"

// scripts includes
#include "camera_movement.h"
#include "scripts/countryManager.h"
#include "engine/colour.h"
#include "Graphics/ShaderManager.h"
#include "loading_screen.h"
#include "engine/Mouse.h"
#include "gamelogic.h"
#include <random>
#include <algorithm>

int clamp(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

void Europe::RenderBatch() {
    render_batch.clear(sf::Color::Transparent);
    for (auto shape : shapes)
    {
        shape.render_shape.setTexture(shape.render_texture);
        render_batch.draw(shape.render_shape);
    }
    render_batch.display();
    render_batch_sprite.setTexture(render_batch.getTexture());
}

std::pair<sf::Sprite, sf::Texture> Europe::pixelizeShape(sf::ConvexShape& shape, float pixelSize, sf::Color shapeColour) {
    sf::RenderTexture renderTexture;
    if (!renderTexture.create(window->getSize().x, window->getSize().y)) {
        std::cout << "Failed to create a render texture of the window size, exiting the program.\n";
        exit(1);
    }

    renderTexture.clear(sf::Color::Transparent);
    shape.setFillColor(shapeColour);
    renderTexture.draw(shape);
    renderTexture.display();

    sf::Texture texture = renderTexture.getTexture();
    sf::Sprite sprite(texture);

    sf::Vector2u textureSize = texture.getSize();

    sf::RenderTexture pixelizedTexture;
    if (!pixelizedTexture.create(textureSize.x / pixelSize, textureSize.y / pixelSize)) {
        std::cout << "Failed to add the pixelated effect, exiting the program.\n";
        exit(1);
    }

    pixelizedTexture.clear(sf::Color::Transparent);
    sprite.setScale(1.0f / pixelSize, 1.0f / pixelSize);
    pixelizedTexture.draw(sprite);
    pixelizedTexture.display();

    sf::Image image = pixelizedTexture.getTexture().copyToImage();

    #define SEED 0
    #define DIFF 10
    srand(SEED);
    for (int x = 0; x < image.getSize().x; ++x) {
        for (int y = 0; y < image.getSize().y; ++y) {
            sf::Color pixel = image.getPixel(x, y);
            if (pixel == sf::Color::Transparent) continue;
            int d = (rand() % (DIFF*2) - DIFF);
            //std::cout << "R: " << pixel.r << "; G: " << pixel.g << "; B: " << pixel.b << "\n";
            pixel = sf::Color(clamp(pixel.r + d, 0, 255), clamp(pixel.g + d, 0, 255), clamp(pixel.b + d, 0, 255), 255);
            image.setPixel(x, y, pixel);
        }
    }

    sf::Texture returnTex;
    returnTex.loadFromImage(image);

    sf::Sprite pixelatedSprite(returnTex);
    pixelatedSprite.setScale(pixelSize, pixelSize);

    return std::pair<sf::Sprite, sf::Texture>{pixelatedSprite, returnTex};
}

void Europe::Awake()
{
    render_batch.create(1280, 720);
    sceneName = "europe";
    // Loading ressources
    std::fstream fgame{"ressources/game.json"};

    game_json = json::parse(fgame);

    std::fstream f{game_json.at("worlds")[(int)(game_json["currentWorld"])]};

    data = json::parse(f);

    currentCountry = "NONE";


    // Loading every countries
    float size = data.at("countries").size();
    float index = 1;
    for (auto country : data.at("countries"))
    {
        LoadingScreen::instance.setValue(index / size * 100.f);
        std::string iso = country["ISO"];
        isos.insert_or_assign(iso, country["name"]);
        colours_iso.insert_or_assign(iso, sf::Color(country.at("colour")["R"], country.at("colour")["G"], country.at("colour")["B"], data["config"]["countryOpacity"]));
        std::cout << TEXT_BLUE "Detected a country!, " << country.at("name") << "[" << country["ISO"] << "]" << RESET_COLOR << "\n";
        for (auto region : country.at("regions"))
        {
            sf::ConvexShape shape{};
            shape.setOutlineColor(sf::Color::Black);
            shape.setOutlineThickness(1.0f);
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
            LoadingScreen::instance.Draw();
            sf::Text txt;
            std::string reg_name = region["name"];
            txt.setScale(sf::Vector2f(region["scale"], region["scale"]));
            txt.setString(reg_name);
            txt.setPosition(sf::Vector2f(region["text_pos"]["X"], region["text_pos"]["Y"]));
            
            auto sh = this->pixelizeShape(shape, 1.f, colours_iso[iso]);
            this->shapes.push_back({shape, iso, reg_name, txt, sh.first, sh.second}); // [own] [rest]
        }
        index++;
    }
    RenderBatch();

    std::cout << "ISO (std::map<std::string, std::string>) size = " << isos.size() << "\n";

    if (data["config"]["EDITOR_SNAPPING_ENABLED"])
    {
        std::cout << TEXT_YELLOW "WARNING: Snapping may cause some performance issues.\n" RESET_COLOR;
    }

    CameraMovement cameraMovement{};
    cameraMovement.view = view;
    cameraMovement.Start();
    scripts.insert_or_assign("1", std::make_unique<CameraMovement>(std::move(cameraMovement)));

    europeReferenceMap.loadFromFile("ressources/images/background.png");
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

    Game::instance.ChangeScene(1);
}

void Europe::Start()
{
    if (gui.Exist("stab")) {
        DynLabel* label = (DynLabel*)gui.components.at("stab")->GetComponent();
        label->Value(std::to_string(client_stability) + "%");
    }
    if (gui.Exist("money")) {
        DynLabel* label = (DynLabel*)gui.components.at("money")->GetComponent();
        label->Value(std::to_string(client_money) + "M$");
    }
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
                    for (int i = 0; i < shape.shape.getPointCount(); ++i)
                    {
                        sf::Vector2f pointB = shape.shape.getPoint(i);
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
        if (S_Mouse::instance.isMouseButtonUp(sf::Mouse::Button::Left)) {
            bool collision = false;
            for (auto shape : shapes)
            {
                if (gui.hovered) {collision = true; break; }
                if (Physics::PIP_Collision(shape.shape, window->mapPixelToCoords(sf::Mouse::getPosition(*window), *view)))
                {
                    // Getting the country from ISO code
                    std::string iso = shape.owner;
                    CountryManager* man = (CountryManager*)scripts.at("countryManager")->getScript();
                    man->selectedCountry = iso;
                    collision = true;
                }
            }
            if (!collision) {
                CountryManager* man = (CountryManager*)scripts.at("countryManager")->getScript();
                man->selectedCountry = "NONE";
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
    this->window->draw(render_batch_sprite);
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

Europe Europe::instance;