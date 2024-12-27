#pragma once
#include "engine.h"
#include "myguilib/GUI.h"
#include "Physics/PIP.h"

class MainMenu: public Scene
{
    public:
    static MainMenu instance;
    MainMenu() = default;
    void Awake() override;
    void Start() override;
    void Update() override;
    void FixedUpdate() override;
    void Draw() override;
};