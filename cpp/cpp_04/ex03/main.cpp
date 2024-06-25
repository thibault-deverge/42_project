#include <iostream>
#include <iostream>
#include <string>
#include "Cure.hpp"
#include "Ice.hpp"
#include "Character.hpp"
#include "MateriaSource.hpp"

int main()
{
    IMateriaSource* src = new MateriaSource();
    src->learnMateria(new Ice());
    src->learnMateria(new Cure());

    ICharacter* me = new Character("me");

    AMateria* tmp;
    tmp = src->createMateria("ice");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);
    // Duplicate of Materia - print error and nothing is done
    me->equip(tmp);
    tmp = src->createMateria("fire"); // do nothing because materia "fire" doesn't exists

    // Code to try overflow of Materia - Add it to garbage
    // me->equip(src->createMateria("cure"));
    // me->equip(src->createMateria("cure"));
    // me->equip(src->createMateria("cure"));
    // me->equip(src->createMateria("cure"));

    ICharacter* bob = new Character("bob");

    me->use(0, *bob);
    me->use(1, *bob);
    me->use(2, *bob); // do nothing because "fire" doesn't exists

    // Test copy constructor using polymorphisme (theme of subject) and casting
    ICharacter* copy = new Character(*static_cast<Character*>(me));
    copy->use(0, *bob); // copy should have the same materias as 'me' (ice)
    
    // Test assignment operator overload using polymorphisme
    ICharacter* assigned = new Character("assigned");
    *static_cast<Character*>(assigned) = *static_cast<Character*>(me);
    assigned->use(1, *bob); // assigned should now also have the same materias as 'me' (cure)

    me->unequip(1);
    me->use(1, *bob); // do nothing because we unequip it before

    delete bob;
    delete me;
    delete src;
    delete copy;
    delete assigned;
    return 0;
}