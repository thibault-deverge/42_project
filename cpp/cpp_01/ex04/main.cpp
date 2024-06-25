#include "utils.hpp"

int main(int argc, char **argv)
{
    try
    {
        if (argc != 4)
            throw std::invalid_argument(ERROR_NB_ARG);

        std::string filename = argv[1];
        std::string str1 = argv[2];
        std::string str2 = argv[3];
        if (filename.empty() || str1.empty())
            throw std::invalid_argument(ERROR_EMPTY_ARG);

        search_and_replace(filename, str1, str2);
    }
    catch(const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}