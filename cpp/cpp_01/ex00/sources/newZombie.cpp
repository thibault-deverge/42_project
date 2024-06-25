#include "Zombie.hpp"

Zombie* newZombie(std::string name)
{
    Zombie* zombie = new (std::nothrow) Zombie(name);
    if (!zombie)
        std::cerr << "error: allocation failed.\n";
    return zombie;
}