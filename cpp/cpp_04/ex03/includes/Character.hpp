#pragma once

#include <iostream>
#include <string>
#include "ICharacter.hpp"
#include "AMateria.hpp"

class Character : public ICharacter
{
private:
    static const std::string M_DEFAULT_NAME;
    static const int M_MAX_ITEMS = 4;
    static const int M_MAX_GARBAGE = 256;

    std::string m_name;
    AMateria*   m_inventory[M_MAX_ITEMS];
    AMateria*   m_garbage[M_MAX_GARBAGE];

    // Helper private functions
    void fillGarbage(AMateria* m);
    void initItemsAndGarbage();

public:
    // Constructors/Destructor
    Character();
    Character(const std::string& name);
    Character(const Character& character);
    ~Character();

    // Operator Overload
    Character& operator=(const Character& rhs);

    // Accessers
    const std::string& getName() const;

    // Members Functions
    void equip(AMateria* m);
    void unequip(int idx);
    void use(int idx, ICharacter& target);
};