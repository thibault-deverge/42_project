#include "Harl.hpp"

/*
 ************ STATIC ARRAYS - MESSAGES ***********
*/
const std::string Harl::_MESSAGES[4] = {
    "I attempted to debug my life, but it seems to be stuck in an infinite loop of procrastination",
    "Fun fact: The 'C' in 'C programming' stands for 'Coffee",
    "Warning: Prolonged exposure to coding may result in a urge to speak in binary code.",
    "Error: My life.exe has encountered unexpected exception. Please reinstall weekends."
};

/*
 ********** MEMBER'S FUNCTION - PRIVATE **********
*/
void Harl::debug() const      { std::cout << _MESSAGES[0] << std::endl; }
void Harl::info() const       { std::cout << _MESSAGES[1] << std::endl; }
void Harl::warning() const    { std::cout << _MESSAGES[2] << std::endl; }
void Harl::error() const      { std::cout << _MESSAGES[3] << std::endl; }

Harl::Level Harl::str_to_level(const std::string& level_str) const
{
    if (level_str == "DEBUG")
    {
        std::cout << "[ DEBUG ]" << std::endl;
        return Level_Debug;
    }
    if (level_str == "INFO")
    {
        std::cout << "[ INFO ]" << std::endl;
        return Level_Info;
    }
    if (level_str == "WARNING")
    {
        std::cout << "[ WARNING ]" << std::endl;
        return Level_Warning;
    }
    if (level_str == "ERROR")
    {
        std::cout << "[ ERROR ]" << std::endl;
        return Level_Error;
    }
    return Level_Unknow;
}

/*
 ****************** CONSTRUCTOR ******************
*/
Harl::Harl() {}

/*
 ********** MEMBER'S FUNCTION - PUBLIC ***********
*/
void Harl::complain(std::string level_str) const
{
    // Transform argument to uppercase
    for (std::size_t i = 0; i < level_str.size(); ++i)
        level_str[i] = toupper(level_str[i]);

    // Switch statement
    Harl::Level level = str_to_level(level_str); 
    switch (level)
    {
        case Level_Debug:
            std::cout << Harl::_MESSAGES[0] << std::endl;
            // Fall Through
        case Level_Info: 
            std::cout << Harl::_MESSAGES[1] << std::endl;
            // Fall Through
        case Level_Warning:
            std::cout << Harl::_MESSAGES[2] << std::endl;
            // Fall Through
        case Level_Error: 
            std::cout << Harl::_MESSAGES[3] << std::endl;
            break;
        default:
            std::cout << "[ Probably complaining about insignificant problems ]\n";
    }
}