#include "Brain.hpp"

/*
** ------------------------- Constructors / Overloads --------------------------
*/
// Public
Brain::Brain() 
{
    std::cout << "Default constructor is called (Brain)\n";
    for (int i = 0; i < m_size_array; ++i)
        m_ideas[i] = "empty";
}

Brain::Brain(const Brain& brain)
{
    std::cout << "Copy constructor was called (Brain)\n";
    *this = brain;
}

Brain::~Brain() 
{ 
    std::cout << "Destructor was called (Brain)\n"; 
}

Brain& Brain::operator=(const Brain& rhs) 
{
    if (this != &rhs)
    {
        for (int i = 0; i < m_size_array; ++i)
            m_ideas[i] = rhs.m_ideas[i];
    }
    return *this;
}

/*
** ------------------------- Public Member Functions ---------------------------
*/
void Brain::fillIdea(std::string value, int idx)
{
    if (idx >= 0 && idx < m_size_array)
        m_ideas[idx] = value += '\n';
    else
        std::cerr << "Impossible to fill Brain at index " << idx << std::endl;
}

const std::string& Brain::getIdea(int idx)
{
    if (idx >= 0 && idx < m_size_array)
        return m_ideas[idx];
    else
    {
        std::cerr << "Index " << idx << " is out of bound.\n";
        // Return first idea if index provided is wrong.
        return m_ideas[0];
    }
}