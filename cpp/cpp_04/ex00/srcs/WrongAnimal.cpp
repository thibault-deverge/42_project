
#include "WrongAnimal.hpp"

/*
** ------------------------- Constructors / Overloads --------------------------
*/
// Public
WrongAnimal::WrongAnimal(): m_type("WrongAnimal") 
{
    std::cout << "Default constructor is called (WrongAnimal)\n";
}


WrongAnimal::WrongAnimal(const WrongAnimal& animal): m_type(animal.getType())
{
    *this = animal;
    std::cout << "Copy constructor was called (WrongAnimal)\n";
}

WrongAnimal::~WrongAnimal() { std::cout << "Destructor was called (WrongAnimal)\n"; }

// Protected
WrongAnimal::WrongAnimal(const std::string& type): m_type(type)
{
    std::cout << "Parameterized constructor is called (WrongAnimal)\n";
}

// Private
WrongAnimal& WrongAnimal::operator=(const WrongAnimal& rhs) 
{
    (void)rhs;
    return *this;
}

/*
** ------------------------- Public Member Functions ---------------------------
*/
void WrongAnimal::makeSound() const { std::cout << "Unrecognizable noise.\n"; }
const std::string& WrongAnimal::getType() const { return m_type; }