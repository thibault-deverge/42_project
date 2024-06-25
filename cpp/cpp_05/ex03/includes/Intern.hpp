#pragma once

#include <iostream>
#include <string>
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern
{
private:
    // Static variables
    static const int M_FORM_NB = 3;
    static const std::string M_FORM_NAME[M_FORM_NB];

    // Helpers functions
    static AForm* createShrubbery(const std::string& target);
    static AForm* createRobotomy(const std::string& target);
    static AForm* createPresidential(const std::string& target);

    // Declaration of Array of pointers to create form
    static AForm* (*M_FORM_CREATION[M_FORM_NB])(const std::string& target);

public:
    // Constructors / Destructors
    Intern();
    Intern(const Intern& intern);
    ~Intern();

    // Assignment overload
    Intern& operator=(const Intern& rhs);

    // Member function
    AForm* makeForm(const std::string& name, const std::string& target);
};