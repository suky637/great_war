#pragma once

#include <string>

class TimeManager {
    public:
    static TimeManager instance;
    std::string getTime(long days);
}