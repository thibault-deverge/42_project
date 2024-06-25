#include <iostream>
#include "Array.hpp"

static const std::string white("\033[0;37m");
static const std::string red("\033[0;31m");
static const std::string blue("\033[0;34m");

int main()
{ 
    try
    {
        // NO-EMPTY ARRAY TEST (parameterized constructor - subscript overload)
        std::cout << blue << "No-empty int array (fill and print):\n" << white;
        Array<int> my_array_parameterized(7);
        for (int i = 0; i < 7; ++i)
            my_array_parameterized[i] = i;
        my_array_parameterized.print();

        // COPY CONSTRUCTOR TEST
        std::cout << blue << "Copy constructor test (print it):\n" << white;
        Array<int> my_array_copy(my_array_parameterized);
        my_array_parameterized.print();

        // ASSIGNMENT OVERLOAD TEST
        std::cout << blue << "Assignment overload test (print it):\n" << white;
        Array<int> my_array_assignment = my_array_copy;
        my_array_assignment.print();

        // MODIFICATION TEST
        std::cout << blue << "Modification value test:\n" << white;
        my_array_assignment[3] = 42;
        my_array_assignment.print();

        //EMPTY ARRAY TEST (Default constructor)
        std::cout << blue << "Make empty array using default constructor:\n";
        Array<int> my_array_default;
        std::cout << white << my_array_default[0] << std::endl; // Throw exception
        std::cout << std::endl;
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << red << "error: " << e.what() << white << '\n';
    }
    catch (const std::bad_alloc& e)
    {
        std::cerr << red << "error: " << e.what() << white << '\n';
    }

    try
    {
        // TEST WITH STD::STRING
        std::cout << blue << "\nTest with class object (Std::String)\n" << white;
        Array<std::string> string_array(5);
        for (int i = 0; i < 5; ++i)
            string_array[i] = "hello";
        string_array.print();

        // TEST EMPTY PASSING 0 TO PARAMETERIZED
        std::cout << blue << "Test with empty array of std::string\n" << white;
        Array<std::string> string_array_empty(0);
        std::cout << white << string_array_empty[0] << std::endl; // throw exception
        std::cout << std::endl;
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << red << "error: " << e.what() << white << '\n';
    }
    catch (const std::bad_alloc& e)
    {
        std::cerr << red << "error: " << e.what() << white << '\n';
    }
    return 0;
}