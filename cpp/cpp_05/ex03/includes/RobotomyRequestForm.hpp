#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include <ctime>
#include <cstdlib>
#include "AForm.hpp"

class RobotomyRequestForm : public AForm
{
private:
    static const std::string    M_NAME;
    static const int            MIN_SIGN = 72;
    static const int            MIN_EXE = 45;

    // Delete assignment operator from public use
    RobotomyRequestForm& operator=(const RobotomyRequestForm& rhs);

public:
    // Constructors / Destructor
    RobotomyRequestForm();
    RobotomyRequestForm(const std::string& target);
    RobotomyRequestForm(const RobotomyRequestForm& form);
    ~RobotomyRequestForm();

    // Members functions
    void action() const;
};