#include "Ice.hpp"

/*
** ------------------------- Constructors / Overloads --------------------------
*/
// Constructors/destructor
Ice::Ice(): AMateria("ice") {}
Ice::Ice(const Ice& ice): AMateria(ice.getType()) {}
Ice::~Ice() {}

/*
** ------------------------- Public member's functions -------------------------
*/
AMateria*   Ice::clone() const
{
    return new Ice();
}

void        Ice::use(ICharacter& target)
{
    std::cout << "* shoots an ice bolt at " << target.getName() << " *\n";
}