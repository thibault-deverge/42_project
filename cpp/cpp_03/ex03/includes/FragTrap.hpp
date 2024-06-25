#pragma once

#include <iostream>
#include <string>
#include "ClapTrap.hpp"

class FragTrap : virtual public ClapTrap
{
private:
    // Helper function
    void init_values();

protected:
    unsigned int    m_hit_points;
    unsigned int    m_damage;

public:
    // Constructors/destructor
    FragTrap();
    FragTrap(const std::string& name);
    FragTrap(const FragTrap& fragtrap);
    ~FragTrap();

    // Operators overload
    FragTrap& operator=(const FragTrap& rhs);

    // Member functions
    void highFivesGuys() const;

    // Getters
    unsigned int        getHitPoints() const;
    unsigned int        getDamage() const;
};