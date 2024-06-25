#include "Animal.hpp"

/*
** ------------------------- Constructors / Overloads --------------------------
*/
// Public
Animal::Animal(): m_type("Animal") 
{
    std::cout << "Default constructor is called (Animal)\n";
}

Animal::Animal(const Animal& animal): m_type(animal.getType())
{
    std::cout << "Copy constructor was called (Animal)\n";
}

Animal::~Animal() { std::cout << "Destructor was called (Animal)\n"; }

// Protected
Animal::Animal(const std::string& type): m_type(type)
{
    std::cout << "Parameterized constructor is called (Animal)\n";
}

/*
** ------------------------- Public Member Functions ---------------------------
*/
void Animal::makeSound() const { std::cout << "Unrecognizable noise.\n"; }
const std::string& Animal::getType() const { return m_type; }