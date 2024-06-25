#pragma once

#include <iostream>
#include <string>
#include "IMateriaSource.hpp"
#include "AMateria.hpp"

class MateriaSource: public IMateriaSource
{
private:
    static const int M_MAX_LEARNT = 4;

    AMateria* m_memory[M_MAX_LEARNT];

public:
    // Constructors/Destructor
    MateriaSource();
    MateriaSource(const MateriaSource& source);
    ~MateriaSource();

    // Operator Overload
    MateriaSource& operator=(const MateriaSource& rhs);

    // Member's functions
    void        learnMateria(AMateria* m);
    AMateria*   createMateria(const std::string& type);
};