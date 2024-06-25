#include "Harl.hpp"

/*
 * ---------- STATIC ARRAYS ----------
*/
const std::string Harl::_MESSAGES[4] = {
    "I attempted to debug my life, but it seems to be stuck in an infinite loop of procrastination",
    "Fun fact: The 'C' in 'C programming' stands for 'Coffee'",
    "Warning: Prolonged exposure to coding may result in a urge to speak in binary code.",
    "Error: My life.exe has encountered unexprected exception. Please reinstall weekends."
};

const std::string Harl::_COMPARISON_STR[4] = {
    "DEBUG",
    "INFO",
    "WARNING",
    "ERROR"
};

/*
 * ---------- CONSTRUCTOR ARRAY ----------
*/
Harl::Harl() 
{
    // Fill the function's pointer array.
    _display_msg[0] = &Harl::debug;
    _display_msg[1] = &Harl::info;
    _display_msg[2] = &Harl::warning;
    _display_msg[3] = &Harl::error;
}

/*
 * ---------- MEMBER'S FUNCTION - PRIVATE ----------
*/
void Harl::debug() const      { std::cout << _MESSAGES[0] << std::endl; }
void Harl::info() const       { std::cout << _MESSAGES[1] << std::endl; }
void Harl::warning() const    { std::cout << _MESSAGES[2] << std::endl; }
void Harl::error() const      { std::cout << _MESSAGES[3] << std::endl; }

/*
 * ---------- MEMBER'S FUNCTION - PUBLIC ----------
*/
void Harl::complain(std::string level) const
{
    // Throw an exception if argument provided is empty (it is not a valid level).
    if (level.empty())
        throw std::invalid_argument("argument provided is empty.");

    // Transform argument to uppercase
    std::string upper_str;
    for (std::size_t i = 0; i < level.size(); ++i)
        upper_str.push_back(toupper(level[i]));

    // Call corresponding function if argument is a valid level;
    for (int i = 0; i < 4; ++i)
    {
        if (!upper_str.compare(_COMPARISON_STR[i]))
        {
            (this->*_display_msg[i])();
            return;
        }
    }

    // Throw an exception if an invalid level is provided.
    throw std::invalid_argument("Invalid level provided to Harl.");
}