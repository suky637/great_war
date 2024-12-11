#include "myguilib/Frame.h"

Frame::Frame(sf::RenderWindow* win, GUI& gui, sf::Vector2f pos, sf::Vector2f size, std::string id, bool visible)
{
    this->win = win;
    this->visible = visible;
    this->position = pos;
    this->size = size;
    this->rect.setPosition(pos);
    this->rect.setSize(size);
    this->rect.setFillColor(sf::Color(61, 61, 61));
    gui.components.insert_or_assign(id == "" ? std::to_string(pos.x) + ";" + std::to_string(pos.y) : id, std::make_unique<Frame>(*this));
}

void Frame::Draw(sf::Font font)
{
    win->draw(this->rect);
}

bool Frame::isHovered(sf::View* view)
{
    sf::Vector2i pos = sf::Mouse::getPosition(*win);
    sf::Vector2f posView = win->mapPixelToCoords(pos, *view);
    return (
        posView.x < this->rect.getPosition().x + this->rect.getSize().x &&
        posView.x > this->rect.getPosition().x &&
        posView.y < this->rect.getPosition().y + this->rect.getSize().y &&
        posView.y > this->rect.getPosition().y
    );
}

std::string Frame::GetType()
{
    return "Frame";
}

Frame* Frame::GetComponent()
{
    return this;
}