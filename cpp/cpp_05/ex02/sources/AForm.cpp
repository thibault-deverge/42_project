#include "AForm.hpp"

const std::string AForm::M_DEFAULT_TARGET = "Angouleme";

/*
** -------------------------------- Exceptions ---------------------------------
*/
const char* AForm::GradeTooHighException::what() const throw()
{
    return "Invalid maximum range";
}

const char* AForm::GradeTooLowException::what() const throw()
{
    return "Invalid minimum range";
}

const char* AForm::FormNotSignedException::what() const throw()
{
    return "Form was not signed previously";
}

void AForm::validate_range() const
{
    if (m_min_range_to_sign > M_MIN_RANGE || m_min_range_to_execute > M_MIN_RANGE)
        throw AForm::GradeTooLowException();
    if (m_min_range_to_execute < M_MAX_RANGE || m_min_range_to_execute < M_MAX_RANGE)
        throw AForm::GradeTooHighException();
}

/*
** ------------------------- Constructors / Overloads --------------------------
*/
AForm::AForm(const std::string& name, const std::string& target, int required_sign, int required_execute)
    : m_name(name),
    m_target(target.empty() ? M_DEFAULT_TARGET : target),
    m_is_signed(false),
    m_min_range_to_sign(required_sign),
    m_min_range_to_execute(required_execute)
{
    validate_range();
}

AForm::AForm(const AForm& form)
    : m_name(form.getName()),
    m_target(form.getTarget()),
    m_is_signed(form.getIsSigned()),
    m_min_range_to_sign(form.getMinRangeToSign()),
    m_min_range_to_execute(form.getMinRangeToExecute())
    {}

// Destructor
AForm::~AForm() {}

// Operator overloads
std::ostream& operator<<(std::ostream& os, const AForm& rhs)
{
    os  << std::endl << "Form: " << rhs.getName() << std::endl
        << "Signed: " << (rhs.getIsSigned() ? "yes" : "no") << std::endl
        << "Target: " << rhs.getTarget() << std::endl
        << "Min to sign: " << rhs.getMinRangeToSign() << std::endl
        << "Min to execute: " << rhs.getMinRangeToExecute() << std::endl;
    return os;
}

/*
** ------------------------- Public Member Functions ---------------------------
*/
// Member functions
void AForm::execute(const Bureaucrat& executor) const
{
    if (!getIsSigned())
        throw AForm::FormNotSignedException();
    if (executor.getRange() > getMinRangeToExecute())
        throw AForm::GradeTooLowException();
    this->action(); 
}

void AForm::beSigned(const Bureaucrat& b)
{
    if (b.getRange() <= m_min_range_to_sign)
        m_is_signed = true;
    else 
        throw AForm::GradeTooLowException();
}

// Accessers
const std::string&  AForm::getName() const { return m_name; }
const std::string&  AForm::getTarget() const { return m_target; }
int                 AForm::getMinRangeToSign() const { return m_min_range_to_sign; }
int                 AForm::getMinRangeToExecute() const { return m_min_range_to_execute; }
bool                AForm::getIsSigned() const { return m_is_signed; }