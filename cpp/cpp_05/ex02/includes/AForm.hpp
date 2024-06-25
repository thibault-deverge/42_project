#pragma once

#include <iostream>
#include <string>
#include "Bureaucrat.hpp"

class Bureaucrat;

class AForm
{
private:
    // Static const variables
    static const std::string    M_DEFAULT_TARGET;
    static const int            M_MAX_RANGE = 1;
    static const int            M_MIN_RANGE = 150;

    // Members variables
    const std::string   m_name;
    const std::string   m_target;
    bool                m_is_signed;
    const int           m_min_range_to_sign;
    const int           m_min_range_to_execute;

    // Helpers functions
    void validate_range() const;

    // Delete assignment operator from public use
    AForm& operator=(const AForm& rhs);

public:
    // Constructors
    AForm();
    AForm(const std::string& name, const std::string& target, int required_sign, int required_execute);
    AForm(const AForm& form);
    virtual ~AForm();

    // Pure virtual functions
    virtual void action() const = 0;

    // Members functions
    void execute(const Bureaucrat& executor) const;
    void beSigned(const Bureaucrat& b);

    // Accessers
    const std::string&  getName() const;
    const std::string&  getTarget() const;
    int                 getMinRangeToSign() const;
    int                 getMinRangeToExecute() const;
    bool                getIsSigned() const;

    // Custom Exceptions
    class GradeTooHighException : public std::exception
    {
    public:
        virtual const char* what() const throw();
    };

    class GradeTooLowException : public std::exception
    {
    public:
        virtual const char* what() const throw();
    };

    class FormNotSignedException : public std::exception
    {
    public:
        virtual const char* what() const throw();
    };
};

// Ostream overload
std::ostream& operator<<(std::ostream& os, const AForm& rhs);