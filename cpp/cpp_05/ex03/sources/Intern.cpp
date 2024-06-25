#include "Intern.hpp"

/*
** --------------------------- Array Initialization ----------------------------
*/
const std::string Intern::M_FORM_NAME[M_FORM_NB] = {
    "Shrubbery Creation",
    "Robotomy Request",
    "Presidential Pardon"
};

AForm* (*Intern::M_FORM_CREATION[M_FORM_NB])(const std::string& target) = {
    &Intern::createShrubbery,
    &Intern::createRobotomy,
    &Intern::createPresidential
};

/*
** ------------------------- Constructors / Overloads --------------------------
*/
// Constructors / Destructor
Intern::Intern() {}
Intern::Intern(const Intern& intern) { *this = intern; }
Intern::~Intern() {}

// Operator Overload
Intern& Intern::operator=(const Intern& rhs)
{
    if (this != &rhs)
        *this = rhs;
    return *this;
}

/*
** ------------------------- Public Member Functions ---------------------------
*/
// Member functions
AForm* Intern::makeForm(const std::string& name, const std::string& target)
{
    for (int i = 0; i < M_FORM_NB; ++i)
    {
        if (name == M_FORM_NAME[i])
        {
            std::cout << "Intern create " << name << std::endl;
            return M_FORM_CREATION[i](target);
        }
    }
    std::cerr   << "Intern canno't create " << name
                << " : it doesn't exists\n";
    return NULL;
}


/*
** ------------------------- Private Member Functions --------------------------
*/
AForm* Intern::createShrubbery(const std::string& target)
{
    return new ShrubberyCreationForm(target);
}

AForm* Intern::createRobotomy(const std::string& target)
{
    return new RobotomyRequestForm(target);
}

AForm* Intern::createPresidential(const std::string& target)
{
    return new PresidentialPardonForm(target);
}