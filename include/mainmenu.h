#pragma once
#include "engine.h"
#include "myguilib.h"
#include "Physics/PIP.h"

class MainMenu: public Scene
{
    private:
    GUI gui;
    public:
    void Start() override;
    void Update() override;
    void FixedUpdate() override;
    void Draw() override;
};