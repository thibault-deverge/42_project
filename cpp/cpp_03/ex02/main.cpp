#include <iostream>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main()
{
    FragTrap titouan("Titouan");
    FragTrap anon;

    titouan.getInfos();
    anon.getInfos();

    anon.attack("");
    anon.takeDamage(20);

    titouan.takeDamage(50);
    titouan.beRepaired(20);
    titouan.takeDamage(50);
    titouan.attack("moskito");
    titouan.beRepaired(20);
    titouan.takeDamage(50);
    titouan.beRepaired(20);

    anon = titouan;
    titouan.getInfos();
    anon.getInfos();
    return 0;
}