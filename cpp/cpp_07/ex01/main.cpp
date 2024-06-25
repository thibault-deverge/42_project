#include <iostream>
#include <string>
#include <cstring>
#include "Iter.hpp"

int main()
{
    // Test on INTEGER array
    std::cout << "Iter called on Int array :\n";
    const int array_int[5] = {1, 2, 3, 4 , 5};
    iter(array_int, 5, printElements<const int>);

    // Test on STD::STRING array
    std::cout << "Iter called on std::string array :\n";
    const std::string array_string[3] = {
        "String 1 -",
        "String 2 -",
        "String 3."
    };
    iter(array_string, 3, printElements<const std::string&>);
    
    // Test on CHAR* array
    std::cout << "Iter called on C style string :\n";
    const char* array_cstring = "Hello, world"; 
    iter(array_cstring, strlen(array_cstring), printElements<const char>);

    // Test on FLOAT array
    std::cout << "Iter called on Float array :\n";
    const float array_float[4] = {1.2f, 2.4f, 3.6f, 4.f};
    iter(array_float, 4, printElements<const float>);

    // Test on BOOL array
    std::cout << "Iter called on Bool array :\n";
    const bool array_bool[5] = {true, false, true, false, true};
    iter(array_bool, 5, printElements<const bool>);

    return 0;
}