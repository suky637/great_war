#pragma once

#include "engine.h"

class CountryManager: public Script
{
    public:
    std::string selectedCountry;
    bool hasSelectedACountry = false;
    void Start() override;
    void Update(GUI* gui) override;
    void FixedUpdate() override;
    void Draw() override;
};