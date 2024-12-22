/*
GWS - Great War Script

Scripting language made by Suky Laplante

*/

#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#undef GUI
#include "myguilib/GUI.h"

enum GWS_EventTypes {
    ON_CLICKED
};

struct GWS_Event {
    GWS_EventTypes type;
    std::string id;
    int start;
    int end;
};

class GWS
{
    private:
    int getEvent(std::string id, GWS_EventTypes type);
    std::vector<std::string> tokens{};
    std::vector<GWS_Event> events{};
    std::vector<std::string> split(std::string& str, std::string delimiters, std::string usefulDel);
    public:
    void interpret(std::string file);
    void runEvent(std::string id, GWS_EventTypes e, GUI* gui);
};
