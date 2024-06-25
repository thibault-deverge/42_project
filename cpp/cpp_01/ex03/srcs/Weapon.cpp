#include "Weapon.hpp"

/*
 *********** STATIC VARIABLE ***********
*/
const std::string Weapon::DEFAULT_WEAPON = "knives";

/*
 ************* CONSTRUCTOR *************
*/
Weapon::Weapon(): _type(DEFAULT_WEAPON) {} 

Weapon::Weapon(const std::string& type): _type(type) 
{
    if (_type.empty())
        _type = DEFAULT_WEAPON;
}

/*
 ********** GETTERS & SETTERS **********
*/
const std::string& Weapon::getType() const { return _type; }

void Weapon::setType(const std::string& type)
{
    if (!type.empty())
        _type = type;
}