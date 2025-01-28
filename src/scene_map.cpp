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

sf::Vector2f getCenter(sf::ConvexShape shape) {
    float area = 0;
    float cx = 0;
    float cy = 0;
    size_t n = shape.getPointCount();

    for (int i = 0; i < n; i++) {
        float x_i = shape.getPoint(i).x;
        float y_i = shape.getPoint(i).y;
        float x_next = shape.getPoint((i + 1) % n).x;
        float y_next = shape.getPoint((i + 1) % n).y;

        float cross = (x_i * y_next - x_next * y_i);

        area += cross;

        cx += (x_i + x_next) * cross;
        cy += (y_i + y_next) * cross;
    }

    area /= 2;
    cx /= (6 * area);
    cy /= (6 * area);
    //std::cout << cx << "; " << cy << "\n";
    return sf::Vector2f(cx, cy);
}

void Europe::ClearBatch() {
    render_batch.clear(sf::Color::Transparent);
}

void Europe::CreateTroopBatch() {
    troopsRender.clear();
    for (auto shape : shapes) {
        int trp = Game::instance.currentSave["tiles"][shape.region_name]["troops"];
        if (trp > 0) {
            // check for adjacent tiles
            bool owned = true;
            bool adjacent = false;
            if (shape.owner != Game::instance.currentCountry) {
                    owned = false;
                    for (const auto& rgN : adjacentPolygons[shape.region_name]) {
                        if (region_to_iso[rgN] == Game::instance.currentCountry) {
                            adjacent = true;
                        }
                    }
            } else {
            }
            if (adjacent || shape.owner == Game::instance.currentCountry) {
                sf::CircleShape troop;
                sf::Vector2f center = getCenter(shape.shape);
                troop.setOutlineColor(sf::Color::Yellow);
                troop.setFillColor(sf::Color(owned ? 0 : 255, 0, owned ? 255 : 0, adjacent ? 70 : 255));
                troop.setPosition(center - sf::Vector2f(1.f, 1.f));
                troop.setRadius(2);
                troopsRender.insert_or_assign(shape.region_name, troop);
            }
        }
    }
}

void Europe::RenderTroops() {
    troop_render_batch.clear(sf::Color::Transparent);
    for (auto const& [k, shape] : troopsRender)
        troop_render_batch.draw(shape);
    troop_render_batch.display();
    troop_render_batch_sprite.setTexture(troop_render_batch.getTexture());
}

void Europe::RenderBatch(bool dontClear) {
    if (!dontClear) {
        ClearBatch();
    }
    for (auto shape : shapes)
    {
        shape.render_shape.setTexture(shape.render_texture);
        render_batch.draw(shape.render_shape);
    }

    RenderTroops();
    
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
    troop_render_batch.create(1280, 720);
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
        std::cout << "ISO: " << iso << "\n";
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

            region_to_iso.insert_or_assign(reg_name, iso);
            
            auto sh = this->pixelizeShape(shape, 1.f, colours_iso[iso]);
            this->shapes.push_back({shape, iso, reg_name, txt, sh.first, sh.second}); // [own] [rest]
        }
        index++;
    }

    if (!std::filesystem::exists("ressources/data/map_cache.json")) {
        CreateAdjacentTerritories();
        // saving to cache
        std::string s = adjacentPolygons.dump();
        std::ofstream __file("ressources/data/map_cache.json", std::ios::out);
        __file << s;
        __file.close();
    }
    else {
        std::fstream fmapcache{"ressources/data/map_cache.json"};
        adjacentPolygons = json::parse(fmapcache);
    }

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

    font.loadFromFile("ressources/StupidMonoSerif-Regular.ttf");

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
    /*pool.push_back(std::async(std::launch::async, [&]() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        while (true) {
            if (S_Mouse::instance.isMouseButtonUp(sf::Mouse::Button::Left)) {
                sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window), *view);
                for (auto [k, troop] : troopsRender) {
                    // point in circle collision
                    if (
                        sqrt(
                            (mousePos.x-(troop.getPosition().x+1.f)) *
                            (mousePos.x-(troop.getPosition().x+1.f)) +
                            (mousePos.y-(troop.getPosition().y+1.f)) * 
                            (mousePos.y-(troop.getPosition().y+1.f))) <= 4.f) {
                        //troopT = true;
                        std::cout << "collision detection\n";
                        troopsRender[k].setOutlineThickness(1);
                        Europe::hasMapChanged = true;
                    }
                    else {
                        troopsRender[k].setOutlineThickness(0);
                    }
                }
            }
        } 
    }));*/
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
    whenAttack.restart();
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

    if (whenAttack.getElapsedTime().asMilliseconds() > 1000) {
        std::vector<int> to_erase{};
        bool mustRerender = false;
        int i = 0;
        for (auto atk : attacks) {
            bool l_mustr = false;
            BattleData battleData;
            battleData.amountOfTroops_Player = Game::instance.currentSave["tiles"][atk.from]["troops"];
            battleData.amountOfTroops_Enemy = Game::instance.currentSave["tiles"][atk.to]["troops"];
            battleData.enemyDefending = true;
            BattleResult result = BattleSystem::simulateBattle(battleData);
            Game::instance.currentSave["tiles"][atk.from]["troops"] = (int)Game::instance.currentSave["tiles"][atk.from]["troops"] - result.damageReceived;
            Game::instance.currentSave["tiles"][atk.to]["troops"] = (int)Game::instance.currentSave["tiles"][atk.to]["troops"] - result.damageSent;
            std::cout << "Received: " << result.damageReceived << " / Sent: " << result.damageSent << "\n";
            std::cout << "Troops (player): " << Game::instance.currentSave["tiles"][atk.from]["troops"] << " / Troops (enemy): " << Game::instance.currentSave["tiles"][atk.to]["troops"] << "\n";
            if (Game::instance.currentSave["tiles"][atk.from]["troops"] <= 0) {
                Game::instance.currentSave["tiles"][atk.from]["troops"] = 0;
                mustRerender = true;
                l_mustr = true;
            }
            if (Game::instance.currentSave["tiles"][atk.to]["troops"] <= 0) {
                Game::instance.currentSave["tiles"][atk.to]["troops"] = 0;
                Game::instance.currentSave["tiles"][atk.to]["owner"] = Game::instance.currentSave["tiles"][atk.from]["owner"];
                // must rerender the whole ass map
                for (int i = 0; i < Europe::instance.shapes.size(); ++i) {
                    if (Europe::instance.shapes[i].region_name != atk.to) continue;
                    auto sh = Europe::instance.pixelizeShape(Europe::instance.shapes[i].shape, 1.f, Europe::instance.colours_iso[Game::instance.currentSave["tiles"][Europe::instance.shapes[i].region_name]["owner"]]);
                    Europe::instance.shapes[i].render_shape = sh.first;
                    Europe::instance.shapes[i].render_texture = sh.second;
                    RenderBatch();
                }
                mustRerender = true;
                l_mustr = true;
            }
            if (l_mustr) {
                to_erase.push_back(i);
            }
            i++;
        }
        for (int ind : to_erase) {
            attacks.erase(attacks.begin() + ind);
        }
        if (mustRerender) {
            CreateTroopBatch();
            RenderTroops();
        }
        whenAttack.restart();
    }

    if (!((!lastFocus && crntFocus) || !crntFocus))
    {
        static bool lastH = false;
        bool crntH = sf::Keyboard::isKeyPressed(sf::Keyboard::H);

        if (!lastH && crntH) hide_placeholder = !hide_placeholder;

        lastH = crntH;

        this->Editor(gui.hovered);

        // just testing something
        if (S_Mouse::instance.isMouseButtonUp(sf::Mouse::Button::Right)) {
            bool troopT = false;
            sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window), *view);
                for (auto [k, troop] : troopsRender) {
                    if (region_to_iso[k] == Game::instance.currentCountry) continue;
                    if (std::find(adjacentPolygons[selectedUnit].begin(), adjacentPolygons[selectedUnit].end(), k) == adjacentPolygons[selectedUnit].end()) continue;
                    // point in circle collision
                    if (
                        sqrt(
                            (mousePos.x-(troop.getPosition().x+1.f)) *
                            (mousePos.x-(troop.getPosition().x+1.f)) +
                            (mousePos.y-(troop.getPosition().y+1.f)) * 
                            (mousePos.y-(troop.getPosition().y+1.f))) <= 4.f) {
                        // Started a battle
                        std::cout << "Battle started!\n";
                        Attack attack;
                        attack.from = selectedUnit;
                        attack.to = k;
                        if (this->findAttack(attack)) {
                            std::cout << "Already made the attack!\n";
                        }else
                            attacks.push_back(attack);
                        
                    }
                }
        }

        if (S_Mouse::instance.isMouseButtonUp(sf::Mouse::Button::Left)) {
            bool collision = false;
            bool troopT = false;
            sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window), *view);
                for (auto [k, troop] : troopsRender) {
                    if (region_to_iso[k] != Game::instance.currentCountry) continue;
                    // point in circle collision
                    if (
                        sqrt(
                            (mousePos.x-(troop.getPosition().x+1.f)) *
                            (mousePos.x-(troop.getPosition().x+1.f)) +
                            (mousePos.y-(troop.getPosition().y+1.f)) * 
                            (mousePos.y-(troop.getPosition().y+1.f))) <= 4.f) {
                        troopsRender[k].setOutlineThickness(1);
                        selectedUnit = k;
                        Europe::hasMapChanged = true;
                    }
                    else {
                        troopsRender[k].setOutlineThickness(0);
                    }
                }
            if (Europe::hasMapChanged || !troopT) {
                //gws
                RenderTroops();
                Europe::hasMapChanged = false;
            }
            
        for (auto shape : shapes)
            if (Physics::PIP_Collision(shape.shape, window->mapPixelToCoords(sf::Mouse::getPosition(*window), *view)))
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

#include "choose_save.h"

void Europe::Draw()
{
    static bool firstTime = true;
    /*if (Game::instance.currentSave.find("tiles") != Game::instance.currentSave.end())
    {
        RenderBatch(false);
        firstTime = false;
    }*/
    this->window->draw(background);

    if (!hide_placeholder)
    {
        referenceImageForEditor.setTexture(&europeReferenceMap);
        this->window->draw(referenceImageForEditor);
    }
    this->window->draw(render_batch_sprite);
    this->window->draw(troop_render_batch_sprite);
    if (preview.getPointCount() >= 3)
        this->window->draw(preview);
    //for (auto a : regi)
    for (auto point : points)
    {
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

void Europe::CreateAdjacentTerritories() {
    for (auto shape : shapes) {
        adjacentPolygons[shape.region_name] = json::array();
        for (auto shape2 : shapes) {
            int pointCommon = 0;
            for (int point_ind2 = 0; point_ind2 < shape2.shape.getPointCount(); ++point_ind2) {
                for (int point_ind = 0; point_ind < shape.shape.getPointCount(); ++point_ind) {
                    if (shape.region_name == shape2.region_name) break;
                    if (shape.shape.getPoint(point_ind) == shape2.shape.getPoint(point_ind2)) {
                        pointCommon++;
                    }
                }
            }
            if (pointCommon > 1) {
                adjacentPolygons[shape.region_name].push_back(shape2.region_name);
            }
        }
    }
}

void Europe::CreateAndRenderTroops() {
    CreateTroopBatch();
    RenderTroops();
}

Europe Europe::instance;

bool Europe::hasMapChanged;

bool Europe::findAttack(Attack attack) {
    for (auto a : attacks) {
        if (a.from == attack.from && a.to == attack.to) return true;
    }
    return false;
}