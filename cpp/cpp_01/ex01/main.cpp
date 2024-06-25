#include <iostream>
#include <cstdlib>
#include "Zombie.hpp"

int main(void)
{
    const int size_horde1 = 5;
    const int size_horde2 = 10;

    Zombie *horde1 = zombieHorde(size_horde1, "Walker");
    if (!horde1)
        return EXIT_FAILURE;

    Zombie *horde2 = zombieHorde(size_horde2, "");
    if (!horde2)
    {
        delete[] horde1;
        return EXIT_FAILURE;
    }

    for (int i = 0; i < size_horde1; ++i)
        horde1[i].announce();
    for (int i = 0; i < size_horde2; ++i)
        horde2[i].announce();

    delete[] horde1;
    delete[] horde2;
    return EXIT_SUCCESS;
}