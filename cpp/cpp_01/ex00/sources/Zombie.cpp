#include "Zombie.hpp"

/*
********** Static Private Variable **********
*/
const std::string Zombie::DEFAULT_NAME = "John Doe";

/*
********** Constructor's & Destructor **********
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
********** Public Methods **********
*/
void Zombie::announce()
{
    std::cout << _name << ": BraiiiiiiinnnzzzZ...\n";
}