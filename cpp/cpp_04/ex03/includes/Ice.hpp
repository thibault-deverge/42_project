#pragma once

#include <iostream>
#include <string>
#include "AMateria.hpp"

class Ice: public AMateria
{
private:
    // Operator Overload
    Ice& operator=(const Ice& rhs);

public:
    // Constructors / Destructor
    Ice();
    Ice(const Ice& ice);
    ~Ice();

    // Member's functions
    AMateria*   clone() const;
    void        use(ICharacter& target);
};