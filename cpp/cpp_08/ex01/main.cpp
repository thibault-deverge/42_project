#include <iostream>
#include <unistd.h>
#include "Span.hpp"

const std::string red("\033[0;31m");
const std::string reset("\033[0m");

int generate_random_nb()
{
    return (rand() % 1000000);
}

int main()
{
    srand(time(0) & getpid());
    {
        try{
            Span sp = Span(5);

            sp.addNumber(6);
            sp.addNumber(3);
            sp.addNumber(17);
            sp.addNumber(9);
            sp.addNumber(11);

            sp.printData();
            std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
            std::cout << "Longest span: " << sp.longestSpan() << std::endl;
            std::cout << std::endl;
        }
        catch(const std::exception& e){
            std::cerr << red << "exception: " << e.what() << reset << '\n';
        }
    }
    {
        try{
            const int range_size = 10;

            // Generate a vector with n random number
            std::vector<int> random_nb(range_size);
            std::generate(random_nb.begin(), random_nb.end(), generate_random_nb);

            // Add these numbers to my span
            Span sp = Span(range_size);
            sp.addNumbers(random_nb.begin(), random_nb.end());

            // Print all dataset, shortest and longest span
            sp.printData();
            std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
            std::cout << "Longest span: " << sp.longestSpan() << std::endl;
            std::cout << std::endl;
        }
        catch(const std::exception& e){
            std::cerr << red << "exception: " << e.what() << reset << '\n';
        }
    }
    // EXCEPTION TEST
    {
        try{
            const int range_size = 10;

            // Generate a vector with n random number
            std::vector<int> random_nb(range_size);
            std::generate(random_nb.begin(), random_nb.end(), generate_random_nb);

            // Make span with insufficient size (throw out_of_range exception)
            Span sp = Span(range_size - 5);
            sp.addNumbers(random_nb.begin(), random_nb.end());
        }
        catch(const std::out_of_range& e){
            std::cerr   << red << "out of range exception: " << reset 
                        << e.what() << '\n';
        }
        catch(const std::exception& e){
            std::cerr   << red << "general exception: " << reset 
                        << e.what() << '\n';
        }
    }
    {
        try{
            Span sp = Span(5);
            // throw exception because sp is empty
            std::cout << sp.shortestSpan() << std::endl;
        }
        catch(const std::length_error& e){
            std::cerr   << red << "length exception: " << reset 
                        << e.what() << '\n';
        }
        catch(const std::exception& e){
            std::cerr   << red << "general exception: " << reset 
                        << e.what() << '\n';
        }
    }

    return 0;
}