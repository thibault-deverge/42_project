#include "HumanA.hpp"

/*
 *********** STATIC VARIABLE ***********
*/
const std::string HumanA::DEFAULT_NAME = "John Doe";

/*
 ************* CONSTRUCTORS ************
*/
HumanA::HumanA(Weapon& weapon): _name(DEFAULT_NAME), _weapon(weapon) {}

HumanA::HumanA(const std::string& name, Weapon& weapon): _name(name), _weapon(weapon)
{
    if (name.empty())
        _name = DEFAULT_NAME;
}

/*
 ************ PUBLIC METHOD ************
*/
void HumanA::attack() const
{
    std::cout << _name << " attacks with their " << _weapon.getType() << std::endl;
}