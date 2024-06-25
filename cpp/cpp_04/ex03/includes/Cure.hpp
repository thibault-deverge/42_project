#pragma once

#include <iostream>
#include <string>
#include "AMateria.hpp"

class Cure: public AMateria
{
private:
    // Operator Overload
    Cure& operator=(const Cure& rhs);

public:
    // Constructors / Destructor
    Cure();
    Cure(const Cure& ice);
    ~Cure();

    // Member's functions
    AMateria*   clone() const;
    void        use(ICharacter& target);
};