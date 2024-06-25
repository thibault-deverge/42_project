#include <iostream>
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main()
{
    try 
    {
        Bureaucrat titouan("titouan", 20);
        Intern titouan_assistant;

        AForm* shrubbery = titouan_assistant.makeForm("Shrubbery Creation", "42");

        titouan.signForm(*shrubbery);
        titouan.executeForm(*shrubbery);

        titouan_assistant.makeForm("Anon form", "home"); // doesn't exists

        delete shrubbery;
    }
    catch (std::exception& e) 
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}