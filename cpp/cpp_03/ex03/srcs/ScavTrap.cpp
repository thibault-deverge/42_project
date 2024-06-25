
#include "ScavTrap.hpp"

/*
** ----------------------------- PRIVATE METHODS -------------------------------
*/
void ScavTrap::init_values()
{
    m_hit_points = 100;
    m_energy_points = 50;
    m_damage = 20;
}

/*
** ------------------------- CONSTRUCTORS / OVERLOAD ---------------------------
*/
ScavTrap::ScavTrap(): ClapTrap() 
{
    std::cout << getName() << " - Default constructor has been called (ScavTrap)\n";
    init_values();
}

ScavTrap::ScavTrap(const std::string& name): ClapTrap(name) 
{
    std::cout << getName() << " - Parameterized constructor has been called (ScavTrap)\n";
    init_values();
}

ScavTrap::ScavTrap(const ScavTrap& scavtrap): ClapTrap(scavtrap) 
{
    std::cout << getName() << " - Copy constructor has been called (ScavTrap)\n";
}

ScavTrap::~ScavTrap() 
{ 
    std::cout << getName() << " - Destructor has been called (ScavTrap)\n"; 
}

ScavTrap& ScavTrap::operator=(const ScavTrap& rhs)
{
    if (this != &rhs)
        ClapTrap::operator=(rhs);
    return *this;
}

/*
** ------------------------------ PUBLIC METHODS -------------------------------
*/
void ScavTrap::guardGate() const
{
    std::cout << "ScavTrap " << getName() << " is now in gate keeper mode.\n";
}

void ScavTrap::attack(const std::string& target)
{
    std::cout << "ScavTrap ";
    if (getEnergyPoints() > 0 && getHitPoints() > 0)
    {   
        std::cout   << getName() << " attack " << (!target.empty() ? target : "nobody") 
                    << ", causing " << getDamage() << " points of damage!\n";
        --m_energy_points;
    }
    else if (getHitPoints() == 0)
        std::cout << getName() << " cannot attack because it's knocked out.\n"; 
    else
        std::cout << getName() << " cannot attack due to lack of energy.\n";
}

unsigned int ScavTrap::getEnergyPoints() const { return m_energy_points; }