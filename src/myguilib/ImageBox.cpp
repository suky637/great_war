#include "myguilib/ImageBox.h"

ImageBox::ImageBox(sf::RenderWindow* win, GUI& gui, sf::Vector2f pos, sf::Vector2f size, std::string _path, std::string id)
{
    this->win = win;
    this->position = pos;
    this->texture.loadFromFile(_path);
    this->rect.setSize(size);
    this->rect.setPosition(pos);
    this->rect.setTexture(&texture);

    gui.components.insert_or_assign(id == "" ? "image" : id, std::make_unique<ImageBox>(*this));
}

void ImageBox::Draw(sf::Font font)
{
    this->rect.setTexture(&texture);
    this->win->draw(this->rect);
}