#pragma once

#include <iostream>
#include <string>
#include "ICharacter.hpp"

class ICharacter;

class AMateria
{
private:
    // prevent copying
    AMateria& operator=(const AMateria& rhs);

protected:
    // Member's variable
    const std::string m_type; 

public:
    // Constructors/destructor
    AMateria();
    AMateria(const std::string& type);
    AMateria(const AMateria& materia);
    virtual ~AMateria();

    // Accessers
    const std::string& getType() const;

    // Member's functions
    virtual AMateria*   clone() const = 0;
    virtual void        use(ICharacter& target) = 0;
};