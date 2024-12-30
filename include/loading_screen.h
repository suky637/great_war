#pragma once
#include "engine.h"
#include "myguilib/GUI.h"
#include "Physics/PIP.h"

class LoadingScreen : public Scene
{
    public:
    sf::RectangleShape rect;
    sf::RectangleShape rect2;
    sf::RectangleShape bg;
    sf::Texture logo;
    sf::Sprite sprite;
    static LoadingScreen instance;
    LoadingScreen() = default;
    void Awake() override;
    void Start() override;
    void Update() override;
    void FixedUpdate() override;
    void Draw() override;
    void setValue(float pourcentage);
};