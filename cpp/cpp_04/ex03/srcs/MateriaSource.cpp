#include "MateriaSource.hpp"


/*
** ------------------------- Constructors / Overloads --------------------------
*/
MateriaSource::MateriaSource() 
{
    for (int i = 0; i < M_MAX_LEARNT; ++i)
        m_memory[i] = 0;
}

MateriaSource::MateriaSource(const MateriaSource& source)
{
    for (int i = 0; i < M_MAX_LEARNT; ++i)
    {
        if (source.m_memory[i])
            m_memory[i] = source.m_memory[i]->clone();
        else
            m_memory[i] = 0;
    }
}

MateriaSource::~MateriaSource() 
{
    for (int i = 0; i < M_MAX_LEARNT; ++i)
    {
        if (m_memory[i])
            delete m_memory[i];
    }
}

MateriaSource& MateriaSource::operator=(const MateriaSource& rhs) 
{
    if (this != &rhs)
    {
        for (int i = 0; i < M_MAX_LEARNT; ++i)
        {
            if (rhs.m_memory[i])
                m_memory[i] = rhs.m_memory[i]->clone();
            else
                m_memory[i] = 0;
        }
    }
    return *this;
}


/*
** ------------------------- Public member's functions -------------------------
*/

void        MateriaSource::learnMateria(AMateria* m) 
{
    int i = 0;

    while (i < M_MAX_LEARNT && m_memory[i])
        i++;
    
    if (i < M_MAX_LEARNT)
        m_memory[i] = m;
    else
    {
        std::cerr << "Source of Materia is full.\n";
        delete m;
    }
}

AMateria*   MateriaSource::createMateria(const std::string& type) 
{
    int i = 3;
    while (i >= 0)
    {
        if  (m_memory[i] && m_memory[i]->getType() == type)
            return m_memory[i]->clone();
        --i;
    }
    return 0;
}