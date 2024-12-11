#include "myguilib/DynImageBox.h"

DynImageBox::DynImageBox(sf::RenderWindow* win, GUI& gui, sf::Vector2f pos, sf::Vector2f size, std::string _path, std::string id, bool visible)
{
    this->win = win;
    this->visible = visible;
    this->path = _path;
    this->position = pos;
    this->texture.loadFromFile(_path);
    this->rect.setSize(size);
    this->rect.setPosition(pos);
    this->rect.setTexture(&texture);

    gui.components.insert_or_assign(id == "" ? "image" : id, std::make_unique<DynImageBox>(*this));
}

void DynImageBox::Draw(sf::Font font)
{
    this->rect.setTexture(&texture);
    this->win->draw(this->rect);
}

void DynImageBox::Value(std::string path)
{
    this->path = path;
    this->texture.loadFromFile(path);
}

std::string DynImageBox::GetType()
{
    return "DynImageBox";
}
DynImageBox* DynImageBox::GetComponent()
{
    return this;
}