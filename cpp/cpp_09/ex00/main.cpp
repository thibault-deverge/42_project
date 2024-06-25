#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include "BitcoinExchange.hpp"
#include "appConstants.hpp"

bool isValidArgc(int argc)
{
    if (argc != 2)
    {
        if (argc < 2)
            std::cerr << "Error: " << ERR_FILE << std::endl;
        else
            std::cerr << "Error: " << ERR_ARGS << std::endl;
        return false;
    }
    return true;
}

int main(int argc, char **argv)
{
    if (!isValidArgc(argc))
        return EXIT_FAILURE;
    
    try
    {
        std::map<std::string, double> database = BitcoinExchange::parseDatabase();
        BitcoinExchange::getValuesWallet(database, argv[1]);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return EXIT_SUCCESS;
}