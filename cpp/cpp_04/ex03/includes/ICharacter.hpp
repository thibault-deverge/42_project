#pragma once

#include <string>
#include "AMateria.hpp"

class AMateria;

class ICharacter
{
public:
    // Destructor
    virtual ~ICharacter() {};

    // Accessers (pure virtual)
    virtual const std::string& getName() const = 0;

    // Member's functions (pure virtual)
    virtual void equip(AMateria* m) = 0;
    virtual void unequip(int idx) = 0;
    virtual void use(int idx, ICharacter& target) = 0;
};