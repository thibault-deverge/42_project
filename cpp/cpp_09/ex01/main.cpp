#include <iostream>
#include "RPN.hpp"

int main(int argc, char **argv)
{
    RPN rpn;

    if (argc != 2)
    {
        std::cout << "Error: Usage: ./program_name 'RPN expression'\n";
        return 1;
    }
    
    try
    {
        rpn.calculate(argv[1]);
    }
    catch(const std::exception& e)
    {
        std::cerr << "error : " << e.what() << '\n';
        return 1;
    }
    return 0;
}