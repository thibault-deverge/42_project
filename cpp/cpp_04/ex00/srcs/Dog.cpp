#include "Dog.hpp"

/*
** ------------------------- Constructors / Overloads --------------------------
*/
// Public
Dog::Dog(): Animal("Dog")
{
    std::cout << "Default constructor is called (Dog)\n";
}

Dog::Dog(const Dog& dog): Animal("Dog")
{
    (void)dog;
    std::cout << "Copy constructor was called (Dog)\n";
}

Dog::~Dog() { std::cout << "Destructor was called (Dog)\n"; }

/*
** ------------------------- Public Member Functions ---------------------------
*/
void Dog::makeSound() const { std::cout << "Wouf wouf\n"; }