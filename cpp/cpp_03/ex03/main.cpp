#include <iostream>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include "DiamondTrap.hpp"

int main()
{
    DiamondTrap titou("Titou");
    DiamondTrap anon;

    titou.getInfos();

    titou.attack("enemy");
    std::cout << std::endl;

    titou.whoAmI();
    std::cout << std::endl;

    return 0;
}