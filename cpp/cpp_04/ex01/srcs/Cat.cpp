#include "Cat.hpp"

/*
** ------------------------- Constructors / Overloads --------------------------
*/
// Public
Cat::Cat(): Animal("Cat"), m_brain(new Brain())
{
    std::cout << "Default constructor is called (Cat)\n";
}

Cat::Cat(const Cat& cat): Animal("Cat")
{
    // Avoid shallow copy by creating new brain using copy operator.
    m_brain = new Brain(*cat.m_brain);
    std::cout << "Copy constructor was called (Cat)\n";
}

Cat::~Cat() 
{ 
    std::cout << "Destructor was called (Cat)\n"; 
    delete m_brain;
}

Cat& Cat::operator=(const Cat& rhs) 
{
    if (this != &rhs)
    {
        // Delete old brain and can call copy constructor of Brain
        // to make a deep copy.
        delete m_brain;
        m_brain = new Brain(*rhs.m_brain);
    }
    return *this;
}

/*
** ------------------------- Public Member Functions ---------------------------
*/
void Cat::makeSound() const { std::cout << "Meoooow\n"; }

void Cat::implementIdea(const std::string& value, int idx)
{
    m_brain->fillIdea(value, idx);
}

const std::string& Cat::getIdea(int idx)
{
    return m_brain->getIdea(idx);
}