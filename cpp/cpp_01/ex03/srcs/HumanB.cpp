#include "HumanB.hpp"

/*
 *********** STATIC VARIABLE ***********
*/
const std::string HumanB::DEFAULT_NAME = "Jane Doe";

/*
 ****** CONSTRUCTORS & DESTRUCTOR ******
*/
HumanB::HumanB(): _name(DEFAULT_NAME), _weapon(NULL) {} 

HumanB::HumanB(Weapon& weapon): _name(DEFAULT_NAME), _weapon(&weapon) {}

HumanB::HumanB(const std::string& name): _name(name), _weapon(NULL)
{
    if (name.empty())
        _name = DEFAULT_NAME;
}

HumanB::HumanB(const std::string& name, Weapon& weapon)
    : _name(name), _weapon(&weapon)
{
    if (name.empty())
        _name = DEFAULT_NAME;
}

/*
 ************ PUBLIC METHOD ************
*/
void HumanB::setWeapon(Weapon& weapon) { _weapon = &weapon; }

void HumanB::attack() const
{
    // If weapon exists : use weapon, otherwise, use hands to attacks.
    const std::string weapon_type = (_weapon ? _weapon->getType() : "hands");

    std::cout << _name << " attacks with their " << weapon_type << std::endl;
}