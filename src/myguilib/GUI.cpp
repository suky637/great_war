#include "myguilib.h"

GUI::GUI()
{

}

GUI::GUI(sf::Font& font)
{
    this->font = sf::Font(font);
}

std::string GUI::getId()
{
    return "GUI";
}

GUI* GUI::getScript()
{
    return this;
}

void GUI::Update(GUI* gui)
{
    this->hovered = false;
    for (const auto& [k, comp] : components)
    {
        comp->Input(view);
        if (comp->isHovered(view))
            this->hovered = true;
    }
}

bool GUI::Exist(std::string compId)
{
    return components.find(compId) != components.end();
}

void GUI::Draw()
{
    window->setView(*view);
    for (const auto& [k, comp] : components)
    {
        if (comp->visible)
            comp->Draw(font);
    }
    //std::cout << "Reached end!\n";
}

bool GUI::isClicked(std::string id)
{
    if (!components.contains(id)) return false;
    return components.at(id)->isClicked;
}

void GUI::getDataByJSON(std::string file, std::string prefix)
{
    std::fstream f{file};
    json dat = json::parse(f);

    std::cout << "Loading " << prefix << "\nLoading font... ";
    std::string pref_config = prefix + std::string("_config");
    if (!font.loadFromFile(dat[pref_config]["font"]))
    {
        std::cerr << "Failed to load font\n";
        exit(1);
    }
    std::cout << "Done\nLoading GUI elements... ";


    for (auto element : dat.at(prefix))
    {
        bool visible = true;
        if (element.find("visible") != element.end())
        {
            visible = element["visible"];
        }
        if (element["type"] == "FRAME")
        {
            sf::Vector2f position{element["position"][0], element["position"][1]};
            sf::Vector2f size{element["scale"][0], element["scale"][1]};
            std::string id = element["id"];

            Frame{window, this, position, size, id, visible};
        }
        else if (element["type"] == "BUTTON")
        {
            std::string text = element["text"];
            std::string id = element["id"];
            sf::Vector2f position{element["position"][0], element["position"][1]};
            sf::Vector2f size{element["scale"][0], element["scale"][1]};

            Button{window, this, position, size, text, id, visible};
        }
        else if (element["type"] == "LABEL")
        {
            std::string text = element["text"];
            std::string id = element["id"];
            sf::Vector2f position{element["position"][0], element["position"][1]};
            int characterSize = element["scale"];

            Label{window, this, position, characterSize, text, id, visible};
        }
        else if (element["type"] == "DYN_LABEL")
        {
            std::string text = element["text"];
            std::string id = element["id"];
            sf::Vector2f position{element["position"][0], element["position"][1]};
            int characterSize = element["scale"];

            DynLabel{window, this, position, characterSize, text, id, visible};
        }
        else if (element["type"] == "IMAGEBOX")
        {
            std::string path = element["path"];
            std::string id = element["id"];
            sf::Vector2f position{element["position"][0], element["position"][1]};
            sf::Vector2f scale{element["scale"][0], element["scale"][1]};

            ImageBox{window, this, position, scale, path, id, visible};
        }
        else if (element["type"] == "DYN_IMAGEBOX")
        {
            std::string path = element["path"];
            std::string id = element["id"];
            sf::Vector2f position{element["position"][0], element["position"][1]};
            sf::Vector2f scale{element["scale"][0], element["scale"][1]};

            DynImageBox{window, this, position, scale, path, id, visible};
        }
    }
    std::cout << "Done\n";
}
//template void GUI::AddComponent<DynImageBox>(sf::Vector2f, std::string, std::string, int, bool);