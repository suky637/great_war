#include "camera_movement.h"
#include <math.h>

CameraMovement::CameraMovement()
{
    zoom = 1.f;
}

void CameraMovement::Start()
{

}

void CameraMovement::ResetZoom(float* accumulation)
{
    float inv = 1.f / *accumulation;
    view->zoom(inv);
    *accumulation = 1.f;
}

void CameraMovement::Update(GUI* gui)
{
    if (gui->hovered) return;
    static float accumulation = 1.f;
    if (scroll == 0)
    {

    }
    else if (scroll == 1)
    {
        accumulation *= 0.97f;
        view->zoom(0.97f);
    }
    else if (scroll == -1)
    {
        accumulation *= 1.03f;
        view->zoom(1.03f);
    }

    // Movement
    #define SPEED 100.f
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        view->move(sf::Vector2f(0, -SPEED * deltaTime * accumulation));
        y += -SPEED * deltaTime * accumulation;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        view->move(sf::Vector2f(0, SPEED * deltaTime * accumulation));
        y += SPEED * deltaTime * accumulation;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        view->move(sf::Vector2f(-SPEED * deltaTime * accumulation, 0));
        x += -SPEED * deltaTime * accumulation;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        view->move(sf::Vector2f(SPEED * deltaTime * accumulation, 0));
        x += SPEED * deltaTime * accumulation;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    {
        ResetZoom(&accumulation);
    }
}

void CameraMovement::FixedUpdate()
{

}

void CameraMovement::Draw()
{

}