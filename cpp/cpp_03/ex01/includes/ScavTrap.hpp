#pragma once

#include <iostream>
#include <string>
#include "ClapTrap.hpp"

class ScavTrap: public ClapTrap 
{
private:
    // Helper function
    void init_values();

public:
    // Constructors/destructor
    ScavTrap();
    ScavTrap(const std::string& name);
    ScavTrap(const ScavTrap& scavtrap);
    ~ScavTrap();

    // Operator overload
    ScavTrap& operator=(const ScavTrap& rhs);

    // Member functions
    void guardGate();
    void attack(const std::string& target);
};