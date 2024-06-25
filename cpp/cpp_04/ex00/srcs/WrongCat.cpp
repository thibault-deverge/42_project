
#include "WrongCat.hpp"

/*
** ------------------------- Constructors / Overloads --------------------------
*/
// Public
WrongCat::WrongCat(): WrongAnimal("Wrong Cat")
{
    std::cout << "Default constructor is called (WrongCat)\n";
}

WrongCat::WrongCat(const WrongCat& cat): WrongAnimal("Wrong cat")
{
    (void)cat;
    std::cout << "Copy constructor was called (WrongCat)\n";
}

WrongCat::~WrongCat() { std::cout << "Destructor was called (WrongCat)\n"; }

/*
** ------------------------- Public Member Functions ---------------------------
*/
void WrongCat::makeSound() const { std::cout << "Meoooow\n"; }