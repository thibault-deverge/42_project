#include <iostream>
#include "Zombie.hpp"

int main( void )
{
	// Create Zombie on the heap
    Zombie* muncher = newZombie("Muncher");
    Zombie* puker = newZombie("Puker");
    if (muncher)
        muncher->announce();
    if (puker)
        puker->announce();

	// Create Zombie on static memory (defeated at at end of function)
    randomChump("");
    randomChump("Groaner");
    randomChump("Putrid");

    // Create Zombie instance with default constructor
    Zombie johnDoe;
    johnDoe.announce();

	// Delete Zombie on the heap
    delete muncher;
    delete puker;
    return 0;
}