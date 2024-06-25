#pragma once

#include <iostream>
#include <string>
#include "Weapon.hpp"

class HumanA
{
private:
    static const std::string DEFAULT_NAME;

    std::string _name;
    Weapon&     _weapon;

public:
    HumanA(Weapon& weapon);
    HumanA(const std::string& name, Weapon& weapon);

    void attack() const;
};