#include "myguilib/Frame.h"

Frame::Frame(sf::RenderWindow* win, GUI* gui, sf::Vector2f pos, sf::Vector2f size, std::string id, bool visible, std::string link_script)
{
    this->win = win;
    this->position = pos;
    this->size = size;
    this->rect.setPosition(pos);
    this->rect.setSize(size);
    this->rect.setFillColor(sf::Color(68, 68, 68));
    this->gui = gui;
    if (link_script != "")
    {
        this->hasLinked = true;
        gws.interpret(link_script);
    }
    SetVisible(visible);
    gui->components.insert_or_assign(id == "" ? std::to_string(pos.x) + ";" + std::to_string(pos.y) : id, std::make_unique<Frame>(*this));
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

void Frame::SetVisible(bool visible) {
    this->visible = visible;
    if (visible) {
        if (hasLinked)
            gws.runEvent(id, GWS_EventTypes::ON_ENABLE, gui);
    else
        if (hasLinked)
            gws.runEvent(id, GWS_EventTypes::ON_DISABLE, gui);
    }
}