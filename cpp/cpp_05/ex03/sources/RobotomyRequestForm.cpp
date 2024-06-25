#include "RobotomyRequestForm.hpp"

const std::string RobotomyRequestForm::M_NAME = "Robotomy Request";

/*
** ------------------------- Constructors / Overloads --------------------------
*/
// Constructors / Destructor
RobotomyRequestForm::RobotomyRequestForm()
    : AForm(M_NAME, "", MIN_SIGN, MIN_EXE) {}

RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
    : AForm(M_NAME, target, MIN_SIGN, MIN_EXE) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& form)
    : AForm(form) {}

RobotomyRequestForm::~RobotomyRequestForm() {}

/*
** ------------------------- Public Member Functions ---------------------------
*/
// Member functions
void RobotomyRequestForm::action() const
{
    srand(time(0) ^ getpid());
    int random_nb = rand() / (RAND_MAX / 2);

    std::cout << "Some VrrrrVrrrr noise happened.\n";
    if (random_nb)
        std::cout << getTarget() << " has been robotomized successfully.\n";
    else
        std::cout << "Robotomy failed on  " << getTarget() << ". Try again\n";
}