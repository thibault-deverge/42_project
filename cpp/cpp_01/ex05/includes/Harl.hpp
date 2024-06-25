#pragma once

#include <iostream>
#include <string>

class Harl
{
private:
    static const std::string _MESSAGES[4];
    static const std::string _COMPARISON_STR[4];

    void (Harl::*_display_msg[4])(void) const;

    void debug() const;
    void info() const;
    void warning() const;
    void error() const;
public:
    Harl();

    void complain(std::string level) const;
};