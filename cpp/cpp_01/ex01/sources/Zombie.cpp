#include "Zombie.hpp"

/*
***** Static variable *****
*/
const std::string Zombie::DEFAULT_NAME = "John Doe";

/*
***** Constructor *****
*/
Zombie::Zombie(): _name(DEFAULT_NAME) {}
Zombie::Zombie(std::string name)
{
    if (name.empty())
        _name = DEFAULT_NAME;
    else
        _name = name;
}
Zombie::~Zombie() 
{
    std::cout << _name << " is defeated.\n";
}

/*
***** Getters & Setters *****
*/
const std::string& Zombie::getName() const { return _name; }

void Zombie::setName(std::string name)
{
    if (!name.empty())
        _name = name;
}

/*
***** Member's function *****
*/
void Zombie::announce()
{
    std::cout << _name << ": BraiiiiiiinnnzzzZ...\n";
}