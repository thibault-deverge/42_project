#include "AMateria.hpp"

/*
** ------------------------- Constructors / Overloads --------------------------
*/
// Constructors/destructor
AMateria::AMateria(): m_type("Abstract") {}
AMateria::AMateria(const std::string& type): m_type(type) {}
AMateria::AMateria(const AMateria& materia): m_type(materia.getType()) {}
AMateria::~AMateria() {}

/*
** ------------------------- Public member's functions -------------------------
*/
const std::string& AMateria::getType() const { return m_type; }