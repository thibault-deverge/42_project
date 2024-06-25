#pragma once

#include <iostream>
#include <string>
#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
private:
    static const std::string    M_NAME;
    static const int            MIN_SIGN = 25;
    static const int            MIN_EXE = 5;

    // Delete assignment operator from public use
    PresidentialPardonForm& operator=(const PresidentialPardonForm& rhs);

public:
    // Constructors / Destructor
    PresidentialPardonForm();
    PresidentialPardonForm(const std::string& target);
    PresidentialPardonForm(const PresidentialPardonForm& form);
    ~PresidentialPardonForm();

    // Members functions
    void action() const;
};