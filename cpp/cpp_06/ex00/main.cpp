#include <iostream>
#include "ScalarConverter.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "error: ./scalar should be run with exactly one argument.\n";
        return 1;
    }
    ScalarConverter::convert(argv[1]);
    return 0;
}