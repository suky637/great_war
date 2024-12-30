#include "loading_screen.h"



void LoadingScreen::Awake() {
    rect.setFillColor(sf::Color::White);
    rect2.setFillColor(sf::Color(39.5f, 40.6f, 47.1f, 255));
    bg.setFillColor(sf::Color(39.5f, 40.6f, 47.1f, 255));
    bg.setSize(sf::Vector2f(1280, 720));
    logo.loadFromFile("ressources/images/logo.png");
    sprite.setTexture(logo);
    sprite.setPosition(sf::Vector2f(1280/2-sprite.getLocalBounds().width/2, 720/2-sprite.getLocalBounds().height/2));
}

void LoadingScreen::Start() {

}

void LoadingScreen::Update() {

}

void LoadingScreen::FixedUpdate() {

}

void LoadingScreen::setValue(float pourcentage) {
    float a = pourcentage / 100.f;
    rect.setSize(sf::Vector2f(720.f * a, 720.f * a));
    rect.setPosition(sf::Vector2f(1280 / 2 - 720*a/2, 720/2 - 720*a/2));
    rect.setFillColor(sf::Color(a*255.f, a*255.f, a*255.f, 255.f));
    rect2.setSize(sf::Vector2f(720.f * a - 10.f, 720.f * a - 10.f));
    rect2.setPosition(sf::Vector2f(1280 / 2 - 720*a/2 + 5.f, 720/2 - 720*a/2 + 5.f));
}

void LoadingScreen::Draw() {
    window->setView(*view);
    window->draw(bg);
    window->draw(rect);
    window->draw(rect2);
    window->draw(sprite);
    window->display();
}

LoadingScreen LoadingScreen::instance;