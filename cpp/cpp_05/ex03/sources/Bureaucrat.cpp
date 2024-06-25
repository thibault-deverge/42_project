#include "Bureaucrat.hpp"

const std::string Bureaucrat::M_DEFAULT_NAME = "John Doe";

/*
** -------------------------------- Exceptions ---------------------------------
*/
const char* Bureaucrat::GradeTooHighException::what() const throw()
{
    return "Bureaucrat exception - Grade is too high";
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
    return "Bureaucrat exception - Grade is too low";
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
// Constructor/Destructor
Bureaucrat::Bureaucrat(): m_name(M_DEFAULT_NAME), m_range(M_DEFAULT_RANGE) {}

Bureaucrat::Bureaucrat(const std::string& name, int range)
    :   m_name(name.empty() ? M_DEFAULT_NAME : name), 
        m_range(range)
{
    validateRange();
}

Bureaucrat::Bureaucrat(const Bureaucrat& bureaucrat)
    : m_name(bureaucrat.getName()), m_range(bureaucrat.getRange()) {}

Bureaucrat::~Bureaucrat() {}

// Operator overload
Bureaucrat& Bureaucrat::operator=(const Bureaucrat& rhs)
{
    // Only assign the range without modifying name (const variable)
    if (this != &rhs)
        m_range = rhs.getRange();
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& rhs)
{
    os << rhs.getName() << ", bureaucrat grade " << rhs.getRange();
    return os;
}

/*
** ------------------------- Public Member Functions ---------------------------
*/
// Member's functions
void Bureaucrat::signForm(AForm& form) const
{
    try
    {
        form.beSigned(*this);
        std::cout << getName() << " signed " << form.getName() << std::endl;
    }
    catch(const AForm::GradeTooLowException& e)
    {
        std::cerr   << getName() << " couldn't sign " << form.getName()
                    << " : " << e.what() << std::endl;
    }
}

void Bureaucrat::executeForm(const AForm& form) const
{
    try
    {
        form.execute(*this);
        std::cout << getName() << " executed " << form.getName() << std::endl;
    }
    catch(const AForm::FormNotSignedException& e)
    {
        std::cerr   << getName() << " couldn't execute " << form.getName()
                    << " : " << e.what() << std::endl;
    }
    catch(const AForm::GradeTooLowException& e)
    {
        std::cerr   << getName() << " couldn't execute " << form.getName()
                    << " : " << e.what() << std::endl;
    }
}

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