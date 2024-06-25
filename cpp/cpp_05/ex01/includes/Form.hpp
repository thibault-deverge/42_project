#pragma once

#include <iostream>
#include <string>
#include "Bureaucrat.hpp"

class Bureaucrat;

class Form
{
private:
    // Static const variables
    static const std::string    M_DEFAULT_NAME;
    static const int            M_DEFAULT_MIN_SIGN = 80;
    static const int            M_DEFAULT_MIN_EXECUTE = 100;
    static const int            M_MAX_RANGE = 1;
    static const int            M_MIN_RANGE = 150;

    // Members variables
    const std::string   m_name;
    bool                m_is_signed;
    const int           m_min_range_to_sign;
    const int           m_min_range_to_execute;

    // Helpers functions
    void validate_range() const;

    // Assignment overload
    Form& operator=(const Form& rhs);

public:
    // Constructors
    Form();
    Form(const std::string& name);
    Form(const std::string& name, int required_sign, int required_execute);
    Form(const Form& form);

    // Destructor
    ~Form();

    // Members functions
    void beSigned(const Bureaucrat& b);

    // Accessers
    const std::string&  getName() const;
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
};

// Ostream overload
std::ostream& operator<<(std::ostream& os, const Form& rhs);