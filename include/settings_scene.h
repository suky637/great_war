#pragma once
#include "engine.h"
#include "myguilib/GUI.h"
#include "Physics/PIP.h"

class Settings_Scene: public Scene {
    public:
    Settings_Scene() = default;
    void Awake() override;
    void Start() override;
    void Update() override;
    void FixedUpdate() override;
    void Draw() override;
};