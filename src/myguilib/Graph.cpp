#include "myguilib/Graph.h"

Graph::Graph(sf::RenderWindow* win, GUI* gui, sf::Vector2f pos, sf::Vector2f size, std::string id, bool visible)
{
    this->win = win;
    this->visible = visible;
    this->position = pos;
    this->size = size;
    this->rect.setPosition(pos);
    this->rect.setSize(size);
    this->rect.setFillColor(sf::Color(0, 0, 0));
    this->gui = gui;
    gui->components.insert_or_assign(id == "" ? std::to_string(pos.x) + ";" + std::to_string(pos.y) : id, std::make_unique<Graph>(*this));
}

void Graph::Draw(sf::Font font)
{
    win->draw(this->rect);
}

bool Graph::isHovered(sf::View* view)
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

std::string Graph::GetType()
{
    return "Graph";
}

Graph* Graph::GetComponent()
{
    return this;
}