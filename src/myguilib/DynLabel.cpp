#include "myguilib/DynLabel.h"
#include "engine/string_manip.h"

DynLabel::DynLabel(sf::RenderWindow* win, GUI* gui, sf::Vector2f pos, int size, std::string text, std::string id, bool visible)
{
    this->win = win;
    this->visible = visible;
    this->position = pos;
    this->label.setFont(gui->font);
    this->label.setString(sf::String(utf8ToUtf32(text)));
    this->label.setCharacterSize(size);
    this->label.setPosition(pos);
    this->label.setFillColor(sf::Color::White);
    this->label.setStyle(sf::Text::Style::Regular);

    gui->components.insert_or_assign(id == "" ? text : id, std::make_unique<DynLabel>(*this));
}

void DynLabel::Draw(sf::Font font)
{
    this->label.setFont(font);
    win->draw(this->label);
}

void DynLabel::Value(std::string value)
{
    this->label.setString(sf::String(utf8ToUtf32(value)));
}

std::string DynLabel::GetType()
{
    return "DynLabel";
}

DynLabel* DynLabel::GetComponent()
{
    return this;
}