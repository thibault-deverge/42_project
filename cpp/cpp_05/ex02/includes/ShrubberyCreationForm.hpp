#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "AForm.hpp"

class ShrubberyCreationForm : public AForm
{
private:
    static const std::string    M_NAME;
    static const int            MIN_SIGN = 145;
    static const int            MIN_EXE = 137;

    // Delete assignment operator from public use
    ShrubberyCreationForm& operator=(const ShrubberyCreationForm& rhs);

    // Helper function
    void drawAsciiTree(std::ostream& file) const;

public:
    // Constructors / Destructor
    ShrubberyCreationForm();
    ShrubberyCreationForm(const std::string& target);
    ShrubberyCreationForm(const ShrubberyCreationForm& form);
    ~ShrubberyCreationForm();

    // Members functions
    void action() const;
};