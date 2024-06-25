#include "Cat.hpp"

/*
** ------------------------- Constructors / Overloads --------------------------
*/
// Public
Cat::Cat(): Animal("Cat")
{
    std::cout << "Default constructor is called (Cat)\n";
}

Cat::Cat(const Cat& cat): Animal("Cat")
{
    (void)cat;
    std::cout << "Copy constructor was called (Cat)\n";
}

Cat::~Cat() { std::cout << "Destructor was called (Cat)\n"; }

/*
** ------------------------- Public Member Functions ---------------------------
*/
void Cat::makeSound() const { std::cout << "Meoooow\n"; }