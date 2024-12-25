#include "myguilib/Label.h"
#include "engine/string_manip.h"

Label::Label(sf::RenderWindow* win, GUI* gui, sf::Vector2f pos, int size, std::string text, std::string id, bool visible)
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

    gui->components.insert_or_assign(id == "" ? text : id, std::make_unique<Label>(*this));
}

void Label::Draw(sf::Font font)
{
    this->label.setFont(font);
    win->draw(this->label);
}

std::string Label::GetType()
{
    return "Label";
}

Label* Label::GetComponent()
{
    return this;
}