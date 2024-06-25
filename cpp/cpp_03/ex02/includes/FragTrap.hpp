#pragma once

#include <iostream>
#include <string>
#include "ClapTrap.hpp"

class FragTrap : public ClapTrap
{
private:
    // Helper function
    void init_values();

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
};