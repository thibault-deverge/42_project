#include <cstdlib>
#include "Harl.hpp"

int main(int argc, char **argv)
{
    // Check number of arguments
    if (argc != 2)
    {
        std::cerr << "Program must have one parameter.\n";
        return EXIT_FAILURE;
    }

    // Check emptiness of argument
    if (!argv[1][0])
    {
        std::cerr << "Parameter cannot be empty.\n";
        return EXIT_FAILURE;
    }

    Harl harl;
    harl.complain(argv[1]);
    return EXIT_SUCCESS; 
}