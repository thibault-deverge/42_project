#include "A_Animal.hpp"

/*
** ------------------------- Constructors / Overloads --------------------------
*/
// Protected
A_Animal::A_Animal(const std::string& type): m_type(type)
{
    std::cout << "Parameterized constructor is called (A_Animal)\n";
}

// Public
A_Animal::~A_Animal() { std::cout << "Destructor was called (A_Animal)\n"; }

/*
** ------------------------- Public Member Functions ---------------------------
*/
const std::string& A_Animal::getType() const { return m_type; }