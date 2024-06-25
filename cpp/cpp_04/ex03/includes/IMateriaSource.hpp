#pragma once

#include <string>
#include "AMateria.hpp"

class IMateriaSource
{
public:
    // Destructor
    virtual ~IMateriaSource() {}
    
    // Member's functions
    virtual void        learnMateria(AMateria*) = 0;
    virtual AMateria*   createMateria(const std::string& type) = 0;
};