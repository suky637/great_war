#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "gamelogic.h"

#define MAX_FPS 1.f / 60.f

void doEvents(sf::RenderWindow* win)
{
    sf::Event event;
    while (win->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
        {
            win->close();
            break;
        }
        case sf::Event::MouseWheelScrolled:
        {
            if (event.mouseWheelScroll.wheel != sf::Mouse::VerticalWheel)
                break;
            float delta = event.mouseWheelScroll.delta;
            Game::instance.scroll = delta;
            break;
            }
         default:
            break;
        }
    }
}

int main(int, char**){


    sf::RenderWindow window{sf::VideoMode(1280, 720), "Window"};
    window.setVerticalSyncEnabled(false);

    Game::instance = Game(&window);

    Game::instance.Begin();
    float lastTime = 0;
    float accumulation = 0;
    sf::Clock clock;

    while (window.isOpen())
    {
        float crntTime = clock.getElapsedTime().asSeconds(); 
        
        doEvents(&window);

        float dt = crntTime - lastTime;
        Game::instance.Update(dt);
        accumulation += dt;
        while (accumulation >= MAX_FPS)
        {
            accumulation -= MAX_FPS;
            Game::instance.FixedUpdate();
        }
        

        Game::instance.Render();

        window.display();

        Game::instance.scroll = 0;
        lastTime = crntTime;
    }

    // Saving everything :)
    Game::instance.Exit();

    return 0;
}
