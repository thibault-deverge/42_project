#include "Cure.hpp"

/*
** ------------------------- Constructors / Overloads --------------------------
*/
// Constructors/destructor
Cure::Cure(): AMateria("cure") {}
Cure::Cure(const Cure& cure): AMateria(cure.getType()) {}
Cure::~Cure() {}

/*
** ------------------------- Public member's functions -------------------------
*/
AMateria*   Cure::clone() const
{
    return new Cure();
}

void        Cure::use(ICharacter& target)
{
    std::cout << "* heals " << target.getName() << "'s wounds *\n";
}