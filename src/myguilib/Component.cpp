#include "myguilib/Component.h"

void Component::Input(sf::View* view)
{
}

void Component::Draw(sf::Font font)
{

}

bool Component::isHovered(sf::View* view)
{
    return false;
}

std::string Component::GetType()
{
    return "";
}
Component* Component::GetComponent()
{
    return this;
}