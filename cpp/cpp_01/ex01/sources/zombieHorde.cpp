#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name)
{
    Zombie* horde = NULL;
    
    if (N > 0)
    {
        horde = new (std::nothrow) Zombie[N];
        if (!horde)
        {
            std::cerr << "error: allocation failed for" << name << std::endl;
            return NULL;
        }
        for (int i = 0; i < N; ++i)
            horde[i].setName(name);
    }
    else
        std::cerr << "error: horde of " << name << " should have positive size.\n";
    return horde;
}