#pragma once

#include <iostream>
#include <string>

class Harl
{
private:
    static const std::string _MESSAGES[4];

    enum Level {
        Level_Debug,
        Level_Info,
        Level_Warning,
        Level_Error,
        Level_Unknow
    };

    void debug() const;
    void info() const;
    void warning() const;
    void error() const;

    Harl::Level str_to_level(const std::string& level_str) const;

public:
    Harl();

    void complain(std::string level) const;
};
