#include <iostream>
#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
    try 
    {
        // First Bureaucrat and Shrubbery Form
        Bureaucrat titouan("titouan", 20);
        AForm* shrubForm = new ShrubberyCreationForm("Home");

        titouan.signForm(*shrubForm); 
        titouan.executeForm(*shrubForm);
        std::cout << std::endl;

        // Second Bureaucrat and RobotomyForm
        Bureaucrat john("john", 5);
        AForm* robotForm = new RobotomyRequestForm("Machine");
        
        john.signForm(*robotForm);
        john.executeForm(*robotForm);
        std::cout << std::endl;

        // Third Bureaucrat and PresidentForm
        Bureaucrat anon("Charlie", 1);
        AForm* presForm = new PresidentialPardonForm("Criminal");

        anon.signForm(*presForm);
        anon.executeForm(*presForm);
        std::cout << std::endl;

        // Fourth Bureaucrat - louis - rank of 5 to be able to sign and execute
        // nb: change to 6 to make it not enough to execute
        // nb2: change to 26 to make it not enough to signed
        std::cout << "--------------------\n";

        Bureaucrat louis("Louis", 26);
        PresidentialPardonForm presForm2("Thiefs");

        std::cout << louis << std::endl;
        std::cout << presForm2 << std::endl;

        louis.signForm(presForm2);
        std::cout << presForm2 << std::endl;

        louis.executeForm(presForm2);

        // Delete all dynamic pointer to form
        delete shrubForm;
        delete robotForm;
        delete presForm;
    }
    catch (std::exception& e) 
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}