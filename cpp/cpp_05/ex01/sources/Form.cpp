#include "Form.hpp"

const std::string Form::M_DEFAULT_NAME = "Daily review";

/*
** -------------------------------- Exceptions ---------------------------------
*/
const char* Form::GradeTooHighException::what() const throw()
{
    return "Form Exception - Invalid maximum range";
}

const char* Form::GradeTooLowException::what() const throw()
{
    return "Form Exception - Invalid minimum range";
}

void Form::validate_range() const
{
    if (m_min_range_to_sign > M_MIN_RANGE || m_min_range_to_execute > M_MIN_RANGE)
        throw Form::GradeTooLowException();
    if (m_min_range_to_execute < M_MAX_RANGE || m_min_range_to_execute < M_MAX_RANGE)
        throw Form::GradeTooHighException();
}

/*
** ------------------------- Constructors / Overloads --------------------------
*/
// Constructor
Form::Form()
    : m_name(M_DEFAULT_NAME), m_is_signed(false),
    m_min_range_to_sign(M_DEFAULT_MIN_SIGN), 
    m_min_range_to_execute(M_DEFAULT_MIN_EXECUTE) 
    {}

Form::Form(const std::string& name)
    : m_name(name.empty() ? M_DEFAULT_NAME : name), 
    m_is_signed(false),
    m_min_range_to_sign(M_DEFAULT_MIN_SIGN),
    m_min_range_to_execute(M_DEFAULT_MIN_EXECUTE)
    {}

Form::Form(const std::string& name, int required_sign, int required_execute)
    : m_name(name.empty() ? M_DEFAULT_NAME : name),
    m_is_signed(false),
    m_min_range_to_sign(required_sign),
    m_min_range_to_execute(required_execute)
{
    validate_range();
}

Form::Form(const Form& form)
    : m_name(form.getName()),
    m_is_signed(form.getIsSigned()),
    m_min_range_to_sign(form.getMinRangeToSign()),
    m_min_range_to_execute(form.getMinRangeToExecute())
    {}

// Destructor
Form::~Form() {}

// Operator overloads
std::ostream& operator<<(std::ostream& os, const Form& rhs)
{
    os  << "Form " << rhs.getName() << " need a range of " << rhs.getMinRangeToSign()
        << " to get signed and " << rhs.getMinRangeToExecute() << " to get execute.\n";
    os  << "Signed : " << (rhs.getIsSigned() ? "yes" : "no");
    return os;
}

/*
** ------------------------- Public Member Functions ---------------------------
*/
// Member variables
void Form::beSigned(const Bureaucrat& b)
{
    if (b.getRange() <= m_min_range_to_sign)
        m_is_signed = true;
    else
        throw Form::GradeTooLowException();
}

// Accessers
const std::string&  Form::getName() const { return m_name; }
int                 Form::getMinRangeToSign() const { return m_min_range_to_sign; }
int                 Form::getMinRangeToExecute() const { return m_min_range_to_execute; }
bool                Form::getIsSigned() const { return m_is_signed; }