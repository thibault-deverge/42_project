#include <iostream>
#include "ClapTrap.hpp"

int main()
{
    ClapTrap toto("Titou");
    ClapTrap anon("");
    ClapTrap louis("Louis");

    toto.getInfos();

    toto.attack("Alexandra");
    toto.attack("");
    toto.attack("Alexandra");
    toto.beRepaired(5);
    toto.beRepaired(5);
    toto.attack("Alexandra");
    toto.attack("");
    toto.beRepaired(5);
    toto.beRepaired(5);
    toto.attack("Alexandra");

    toto.getInfos();

    toto.attack("");
    toto.takeDamage(15);
    toto.takeDamage(20);
    toto.beRepaired(5);

    anon = louis;
    anon.getInfos();

    return 0;
}