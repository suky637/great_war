#include "myguilib/GUI.h"

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

void GUI::Update(bool gui_hovered)
{
    this->hovered = false;
    for (const auto& [k, comp] : components)
    {
        comp->Input(gui_view);
        if (comp->isHovered(gui_view))
            this->hovered = true;
    }
}

void GUI::Draw()
{
    window->setView(*gui_view);
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