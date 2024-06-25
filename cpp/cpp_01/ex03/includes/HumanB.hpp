#pragma once

#include <iostream>
#include <string>
#include "Weapon.hpp"

class HumanB
{
private:
    static const std::string DEFAULT_NAME;

    std::string     _name;
    Weapon*         _weapon;

public:
    HumanB();
    HumanB(Weapon& weapon);
    HumanB(const std::string& name);
    HumanB(const std::string& name, Weapon& weapon);

    void setWeapon(Weapon& weapon);

    void attack() const;
};