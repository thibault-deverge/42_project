#include "Bureaucrat.hpp"

const std::string Bureaucrat::M_DEFAULT_NAME = "John Doe";

/*
** -------------------------------- Exceptions ---------------------------------
*/
const char* Bureaucrat::GradeTooHighException::what() const throw()
{
    return "Grade is too high - Maximum grade is 1";
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
    return "Grade is too low - Lowest grade is 150";
}

void Bureaucrat::validateRange() const
{
    if (m_range < M_MAX_RANGE)
        throw Bureaucrat::GradeTooHighException();
    if (m_range > M_MIN_RANGE)
        throw Bureaucrat::GradeTooLowException();
}

/*
** ------------------------- Constructors / Overloads --------------------------
*/
// Constructors
Bureaucrat::Bureaucrat(): m_name(M_DEFAULT_NAME), m_range(M_DEFAULT_RANGE) {}

Bureaucrat::Bureaucrat(int range): m_name(M_DEFAULT_NAME), m_range(range)
{
    validateRange();
}

Bureaucrat::Bureaucrat(const std::string& name)
    :   m_name(name.empty() ? M_DEFAULT_NAME : name),
        m_range(M_DEFAULT_RANGE)
        {}

Bureaucrat::Bureaucrat(const std::string& name, int range)
    :   m_name(name.empty() ? M_DEFAULT_NAME : name), 
        m_range(range)
{
    validateRange();
}

Bureaucrat::Bureaucrat(const Bureaucrat& bureaucrat)
    : m_name(bureaucrat.getName()), m_range(bureaucrat.getRange()) {}


// Destructor
Bureaucrat::~Bureaucrat() {}

// Operator overload
Bureaucrat& Bureaucrat::operator=(const Bureaucrat& rhs)
{
    // Only assign the range without modifying name (const variable)
    if (this != &rhs)
        m_range = rhs.getRange();
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& b)
{
    os << b.getName() << ", bureaucrat grade " << b.getRange();
    return os;
}

/*
** ------------------------- Public Member Functions ---------------------------
*/
// Member's functions
void Bureaucrat::increment()
{
    --m_range;
    validateRange();
}

void Bureaucrat::decrement()
{
    ++m_range;
    validateRange();
}

// Accessers
const std::string&  Bureaucrat::getName() const { return m_name; }
int                 Bureaucrat::getRange() const { return m_range; }