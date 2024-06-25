#include "ClapTrap.hpp"

const std::string ClapTrap::M_DEFAULT_NAME = "John Doe";

/*
** ------------------------- CONSTRUCTORS / OVERLOAD ---------------------------
*/
ClapTrap::ClapTrap()
    : m_name(ClapTrap::M_DEFAULT_NAME), m_hit_points(10), 
    m_energy_points(10), m_damage(0) 
{
    std::cout << getName() << " - Default constructor has been called (ClapTrap)\n";
}

ClapTrap::ClapTrap(const std::string& name)
    : m_name(name), m_hit_points(10), 
    m_energy_points(10), m_damage(0) 
{
    if (name.empty())
        m_name = ClapTrap::M_DEFAULT_NAME;
    std::cout << getName() << " - Parameterized constructor has been called (ClapTrap)\n";
}

ClapTrap::ClapTrap(const ClapTrap& claptrap) 
{ 
    *this = claptrap; 
    std::cout << getName() << " - Copy constructor has been called (ClapTrap)\n";
}

ClapTrap::~ClapTrap() 
{ 
    std::cout << getName() << " - Destructor has been called (ClapTrap)\n"; 
}

ClapTrap& ClapTrap::operator=(const ClapTrap& rhs)
{
    if (this != &rhs)
    {
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
void    ClapTrap::getInfos() const
{
    std::cout   << "---------------\n"
                << "name : "            << getName() << std::endl
                << "hit points : "      << getHitPoints() << std::endl
                << "energy points : "   << getEnergyPoints() << std::endl
                << "damage : "          << getDamage() << std::endl
                << "---------------\n";
}

void    ClapTrap::attack(const std::string& target)
{
    std::cout << "ClapTrap ";
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

void    ClapTrap::takeDamage(unsigned int amount)
{
    std::cout << "ClapTrap ";
    if (getHitPoints() <= amount)
    {
        std::cout << getName() << " has taken too much damages and is knocked out.\n";
        m_hit_points = 0;
    }
    else
    {
        m_hit_points -= amount;
        std::cout   << getName() << " has taken " << amount << " damages and still has " 
                    << getHitPoints() << " left.\n";
    }
}

void    ClapTrap::beRepaired(unsigned int amount)
{
    std::cout << "ClapTrap ";
    if (getEnergyPoints() > 0 && getHitPoints() > 0)
    {
        m_hit_points += amount;
        --m_energy_points;
        std::cout << getName() << " heals himself. He now have " << getHitPoints() << " hit points.\n";
    }
    else if (getHitPoints() == 0)
        std::cout << getName() << " cannot heal because it's knocked out.\n"; 
    else
        std::cout << getName() << " cannot heal due to lack of energy.\n";
}

/*
** --------------------------------- ACCESSERS ---------------------------------
*/
const std::string&  ClapTrap::getName() const { return m_name; }
unsigned int        ClapTrap::getHitPoints() const { return m_hit_points; }
unsigned int        ClapTrap::getEnergyPoints() const { return m_energy_points; }
unsigned int        ClapTrap::getDamage() const { return m_damage; }