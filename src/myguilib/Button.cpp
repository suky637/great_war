#include "myguilib/Button.h"

Button::Button(
    sf::RenderWindow* win, 
    GUI* gui, 
    sf::Vector2f pos, 
    sf::Vector2f size, 
    std::string text, 
    std::string id, 
    bool visible, 
    std::string linkScript
)
{
    this->win = win;
    this->position = pos;
    this->size = size;
    this->visible = visible;
    

    this->rect.setSize(size);
    this->rect.setPosition(pos);
    this->rect.setFillColor(sf::Color(91, 91, 91));

    this->label.setFont(gui->font);
    this->label.setString(text);
    this->label.setCharacterSize(64);
    float scaleMultiplicator = size.y / 66;
    this->label.setScale(sf::Vector2f(scaleMultiplicator, scaleMultiplicator));
    this->label.setFillColor(sf::Color::White);
    this->label.setStyle(sf::Text::Regular);

    const sf::FloatRect textRect = this->label.getLocalBounds();

    //this->label.setOrigin(xOff, yOff);
    this->label.setPosition(
        position.x + (size.x / 2) - (textRect.width * scaleMultiplicator / 2), 
        position.y + (size.y / 2) - (textRect.height * scaleMultiplicator / 2 + 4 * (size.y / 20))
    );
    
    this->id = id == "" ? text : id;

    //1std::cout << "Created Button Sucessfuly!\n";
    if (linkScript != "")
    {
        this->hasLinked = true;
        //std::cout << "Linked the button [" << this->id << "] to " << linkScript << "!\n";
        gws.interpret(linkScript);
    }
    gui->components.insert_or_assign(this->id, std::make_unique<Button>(*this));
}

void Button::setGUI(GUI* gui)
{
    this->gui = gui;
}

void Button::Input(sf::View* view)
{
    isClicked = false;
    // Checking if hovering

    if (this->isHovered(view))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            //std::cout << "CLICK BUTTON\n";
            lastClick = crntClicked;
            crntClicked = true;
        }
        else
        {
            crntClicked = false;
        }
        if (!crntClicked && lastClick)
        {
            isClicked = true;
            
            if (hasLinked)
                gws.runEvent(id, GWS_EventTypes::ON_CLICKED, gui);
            
            lastClick = false;
        }

        rect.setFillColor(sf::Color(81, 81, 81));
        return;
    }
    rect.setFillColor(sf::Color(91, 91, 91));
    
}

void Button::Draw(sf::Font font)
{
    //std::cout << "DRAW\n";
    if (win == nullptr)
        return;
    
    win->draw(rect);
    label.setFont(font);
    win->draw(label);
}

bool Button::isHovered(sf::View* view)
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

std::string Button::GetType()
{
    return "Button";
}

Button* Button::GetComponent()
{
    return this;
}