#pragma once
#include "engine.h"
#include "myguilib/GUI.h"
#include "Physics/PIP.h"

class ChooseSave: public Scene
{
    public:
    ChooseSave() = default;
    static ChooseSave instance;
    void createData();
    void loadData();
    void Awake() override;
    void Start() override;
    void Update() override;
    void FixedUpdate() override;
    void Draw() override;
};