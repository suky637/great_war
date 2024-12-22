#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <map>
#include <memory>

#include "engine.h"
#include "myguilib/GUI.h"

class CameraMovement: public Script
{
    private:
    void ResetZoom(float* acc);
    public:
    float x;
    float y;
    CameraMovement();
    float zoom;
    void Start() override;
    void Update(GUI* gui) override;
    void FixedUpdate() override;
    void Draw() override;
};