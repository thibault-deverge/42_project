#include "FragTrap.hpp"

/*
** ----------------------------- PRIVATE METHODS -------------------------------
*/
void FragTrap::init_values()
{
    m_hit_points = 100;
    m_energy_points = 100;
    m_damage = 30;
}

/*
** ------------------------- CONSTRUCTORS / OVERLOAD ---------------------------
*/
FragTrap::FragTrap(): ClapTrap()
{
    std::cout << getName() << " - Default constructor has been called (FragTrap)\n";
    init_values();
}

FragTrap::FragTrap(const std::string& name): ClapTrap(name)
{
    std::cout << getName() << " - Parameterized constructor has been called (FragTrap)\n";
    init_values();
}

FragTrap::FragTrap(const FragTrap& fragtrap): ClapTrap(fragtrap)
{
    std::cout << getName() << " - Copy constructor has been called (FragTrap)\n";
}

FragTrap::~FragTrap() 
{ 
    std::cout << getName() << " - Destructor has been called (FragTrap)\n"; 
}

FragTrap& FragTrap::operator=(const FragTrap& rhs)
{
    if (this != &rhs)
        ClapTrap::operator=(rhs);
    return *this;
}

/*
** ------------------------------ PUBLIC METHODS -------------------------------
*/
void FragTrap::highFivesGuys() const
{
    std::cout << "FragTrap " << getName() << " wants to high five the other guys.\n";
}