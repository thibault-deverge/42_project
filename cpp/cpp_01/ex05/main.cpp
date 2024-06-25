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

    Harl harl;
    try {
        harl.complain(argv[1]);
    }
    catch(const std::exception& error) {
        std::cerr << error.what() << '\n';
    }
    return EXIT_SUCCESS; 
}