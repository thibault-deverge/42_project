#pragma once

#include <iostream>
#include <string>
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

class DiamondTrap: public ScavTrap, public FragTrap
{
private:
    static const std::string M_DEFAULT_NAME;

    std::string     m_name;

    // Helper function
    void init_values();
public:
    // Constructors/destructor
    DiamondTrap();
    DiamondTrap(const std::string& name);
    DiamondTrap(const DiamondTrap& diamond);
    ~DiamondTrap();

    // Operators overload
    DiamondTrap& operator=(const DiamondTrap& rhs);

    // Member functions
    void getInfos() const;
    void attack(const std::string& target);
    void whoAmI() const;

    // Accessers
    const std::string&  getName() const;
};