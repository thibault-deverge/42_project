#pragma once

#include <iostream>
#include <string>
#include "ClapTrap.hpp"

class ScavTrap: virtual public ClapTrap 
{
private:
    // Helper function
    void init_values();

protected:
    unsigned int    m_energy_points;

public:
    // Constructors/destructor
    ScavTrap();
    ScavTrap(const std::string& name);
    ScavTrap(const ScavTrap& scavtrap);
    ~ScavTrap();

    // Operators overload
    ScavTrap& operator=(const ScavTrap& rhs);

    // Member functions
    void guardGate() const;
    void attack(const std::string& target);

    // Getters
    unsigned int        getEnergyPoints() const;
};