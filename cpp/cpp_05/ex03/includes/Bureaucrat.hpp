#pragma once

#include <iostream>
#include <string>
#include "AForm.hpp"

class AForm;

class Bureaucrat
{
private:
    // Static Members variables
    static const std::string    M_DEFAULT_NAME;
    static const int            M_DEFAULT_RANGE = 75;
    static const int            M_MAX_RANGE = 1;
    static const int            M_MIN_RANGE = 150;

    // Members variables
    const std::string   m_name;
    int                 m_range;

    // Helpers function
    void validateRange() const;

public:
    // Constructors
    Bureaucrat();
    Bureaucrat(const std::string& name, int range);
    Bureaucrat(const Bureaucrat& bureaucrat);

    // Destructor
    ~Bureaucrat();

    // Assignment Overload (only copy range - name is const)
    Bureaucrat& operator=(const Bureaucrat& rhs);

    // Members functions
    void signForm(AForm& form) const;
    void executeForm(const AForm& form) const;
    void increment();
    void decrement();

    // Accessers
    const std::string&  getName() const;
    int                 getRange() const;

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
std::ostream& operator<<(std::ostream& os, const Bureaucrat& rhs);