#pragma once

#include <iostream>
#include <string>

class ClapTrap
{
private:
    static const std::string M_DEFAULT_NAME;

protected:
    std::string     m_name;
    unsigned int    m_hit_points;
    unsigned int    m_energy_points;
    unsigned int    m_damage;

public:
    // Constructors/destructor
    ClapTrap();
    ClapTrap(const std::string& name);
    ClapTrap(const ClapTrap& claptrap);
    ~ClapTrap();

    // Operator overload
    ClapTrap& operator=(const ClapTrap& rhs);

    // Member functions
    void getInfos() const;
    void attack(const std::string& target);
    void takeDamage(unsigned int amount);
    void beRepaired(unsigned int amount);

    // Getters
    const std::string&  getName() const;
    unsigned int        getHitPoints() const;
    unsigned int        getEnergyPoints() const;
    unsigned int        getDamage() const;
};