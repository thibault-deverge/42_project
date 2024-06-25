#include <iostream>
#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
    try
    {
        Bureaucrat anon_bureaucrat;
        Bureaucrat titou("Titouan", 60);
        Bureaucrat louis("Louis", 140);

        Form anon_form;
        Form bill("bill");
        Form tax("Tax 2023", 45, 35);
        // Form invalid("nope", 23, -10); // Invalid range to execute

        std::cout << "Bureaucrat :\n";
        std::cout << anon_bureaucrat << std::endl;
        std::cout << titou << std::endl;
        std::cout << louis << std::endl;
        std::cout << std::endl;

        std::cout << "Form :\n";
        std::cout << anon_form << std::endl;
        std::cout << tax << std::endl;
        std::cout << bill << std::endl;
        std::cout << std::endl;

        titou.signForm(anon_form);
        titou.signForm(tax);
        std::cout << anon_form << std::endl;
        std::cout << tax << std::endl;

        titou.decrement();
        // titou.decrement(); // throw an exception GradeTooLow

        std::cout << std::endl;
        louis.signForm(bill);
        std::cout << "Louis is assigned Titouan's range\n";
        louis = titou;
        louis.signForm(bill);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}