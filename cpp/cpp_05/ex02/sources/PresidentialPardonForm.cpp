#include "PresidentialPardonForm.hpp"

const std::string PresidentialPardonForm::M_NAME = "Presidential Pardon";

/*
** ------------------------- Constructors / Overloads --------------------------
*/
// Constructors / Destructor
PresidentialPardonForm::PresidentialPardonForm()
    : AForm(M_NAME, "", MIN_SIGN, MIN_EXE) {}

PresidentialPardonForm::PresidentialPardonForm(const std::string& target)
    : AForm(M_NAME, target, MIN_SIGN, MIN_EXE) {}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& form)
    : AForm(form) {}

PresidentialPardonForm::~PresidentialPardonForm() {}

/*
** ------------------------- Public Member Functions ---------------------------
*/
// Member functions
void PresidentialPardonForm::action() const
{
    std::cout << getTarget() << " has been pardonned by Zaphod Beeblebrox.\n";
}