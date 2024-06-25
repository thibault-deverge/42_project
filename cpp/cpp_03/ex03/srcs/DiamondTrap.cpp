#include "DiamondTrap.hpp"

const std::string DiamondTrap::M_DEFAULT_NAME = "Jane Doe";

/*
** ----------------------------- PRIVATE METHODS -------------------------------
*/
void DiamondTrap::init_values()
{
    m_hit_points = FragTrap::getHitPoints();
    m_energy_points = ScavTrap::getEnergyPoints();
    m_damage = FragTrap::getDamage();
}

/*
** ------------------------- CONSTRUCTORS / OVERLOAD ---------------------------
*/
DiamondTrap::DiamondTrap(): ClapTrap(DiamondTrap::M_DEFAULT_NAME + "_clap_trap"), ScavTrap(), FragTrap()
{
    m_name = DiamondTrap::M_DEFAULT_NAME;
    init_values();
    std::cout << m_name << " - Default constructor has been called (DiamondTrap)\n";
}

DiamondTrap::DiamondTrap(const std::string& name): ClapTrap(name + "_clap_trap"), ScavTrap(name), FragTrap(name)
{
    m_name = name;
    init_values();
    std::cout << getName() << " - Parameterized constructor has been called (DiamondTrap)\n";
}

DiamondTrap::DiamondTrap(const DiamondTrap& diamond): ClapTrap(), ScavTrap(), FragTrap()
{
    *this = diamond;
    std::cout << getName() << " - Copy constructor has been called (DiamondTrap)\n";
}

DiamondTrap::~DiamondTrap() 
{
    std::cout << getName() << " - Destructor has been called (DiamondTrap)\n"; 
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& rhs)
{
    if (this != &rhs)
    {
        ClapTrap::m_name = rhs.getName() + "_clap_trap";
        m_name = rhs.getName();
        m_hit_points = rhs.getHitPoints();
        m_energy_points = rhs.getEnergyPoints();
        m_damage = rhs.getDamage();
    }
    return *this;
}

/*
** ------------------------------ PUBLIC METHODS -------------------------------
*/
void    DiamondTrap::getInfos() const
{
    std::cout   << "---------------\n"
                << "name : "            << getName() << std::endl
                << "hit points : "      << getHitPoints() << std::endl
                << "energy points : "   << getEnergyPoints() << std::endl
                << "damage : "          << getDamage() << std::endl
                << "---------------\n";
}

void DiamondTrap::attack(const std::string& target)
{
    ScavTrap::attack(target);
}

void DiamondTrap::whoAmI() const
{
    std::cout << "DiamondTrap name is : " << m_name << std::endl;
    std::cout << "ClapTrap name is : " << ClapTrap::m_name << std::endl;
}

const std::string&  DiamondTrap::getName() const { return m_name; }