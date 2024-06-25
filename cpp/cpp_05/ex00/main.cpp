#include <iostream>
#include "Bureaucrat.hpp"

int main()
{
    try
    {
        Bureaucrat anon;
        Bureaucrat titou("Titouan", 149);
        Bureaucrat eloi("eguillau", 85);
        // Bureaucrat maxime("Mlauro", 0); // throw an exception GradeTooHigh
        Bureaucrat john("");

        std::cout << anon << std::endl;
        std::cout << titou << std::endl;
        std::cout << eloi << std::endl;
        std::cout << john << std::endl; // "john doe" because empty string when created

        titou = eloi;
        std::cout << titou << std::endl;

        titou.decrement();
        // titou.decrement(); // throw an exception GradeTooLow
    }
    catch(const Bureaucrat::GradeTooHighException& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    catch (const Bureaucrat::GradeTooLowException& e)
    {
        std::cerr << e.what() << '\n';
        return 2;
    }
    return 0;
}