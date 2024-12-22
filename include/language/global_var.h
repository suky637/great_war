#pragma once

#include <map>
#include <string>

class GWS_Variables {
    public:
    static GWS_Variables instance;
    std::map<std::string, std::string> variables;
    GWS_Variables() = default;
};