#include <iostream>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main()
{
    ScavTrap john;
    ScavTrap scav("Titouan");
    ScavTrap scav2(scav);

    john.getInfos();
    scav.getInfos();
    scav2.getInfos();

    john.attack("mouse");
    scav.attack("squirrel");
    scav.attack("squirrel");
    scav.beRepaired(10);
    scav2.guardGate();

    scav2 = john;
    
    john.getInfos();
    scav.getInfos();
    scav2.getInfos();
    return 0;
}