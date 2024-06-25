#include "Dog.hpp"

/*
** ------------------------- Constructors / Overloads --------------------------
*/
// Public
Dog::Dog(): Animal("Dog"), m_brain(new Brain())
{
    std::cout << "Default constructor is called (Dog)\n";
}

Dog::Dog(const Dog& dog): Animal("Dog")
{
    // Avoid shallow copy by creating new brain by using copy constructor.
    m_brain = new Brain(*dog.m_brain);
    std::cout << "Copy constructor was called (Dog)\n";
}

Dog::~Dog() 
{ 
    std::cout << "Destructor was called (Dog)\n"; 
    delete m_brain;
}

Dog& Dog::operator=(const Dog& rhs) 
{
    if (this != &rhs)
    {
        // Delete old brain and make new one using copy constructor of it
        delete m_brain;
        m_brain = new Brain(*rhs.m_brain);
    }
    return *this;
}

/*
** ------------------------- Public Member Functions ---------------------------
*/
void Dog::makeSound() const { std::cout << "Wouf wouf\n"; }

void Dog::implementIdea(const std::string& value, int idx)
{
    m_brain->fillIdea(value, idx);
}

const std::string& Dog::getIdea(int idx)
{
    return m_brain->getIdea(idx);
}