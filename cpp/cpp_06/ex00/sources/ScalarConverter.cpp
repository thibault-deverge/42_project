#include "ScalarConverter.hpp"

// --------------------------------- PUBLIC ------------------------------------
void ScalarConverter::convert(const std::string& arg)
{
    int code_regex = 0;

    // Find data-type received as argument
    code_regex = RegexDataType::findDataType(arg.c_str());
    if (code_regex == M_REGEX_FAIL || code_regex == M_REGEX_NOMATCH)
        return ;
    
    std::cout << std::fixed << std::setprecision(1);
    if (code_regex == RegexDataType::M_CHAR)
        convertFromChar(arg);
    else if (code_regex == RegexDataType::M_INT)
        convertFromInt(arg);
    else if (code_regex == RegexDataType::M_FLOAT)
        convertFromFloat(arg);
    else if (code_regex == RegexDataType::M_DOUBLE)
        convertFromDouble(arg);
}

// --------------------------------- PRIVATE -----------------------------------

/*
** --------------------------------- Convert -----------------------------------
*/
void ScalarConverter::convertFromChar(const std::string& arg_str)
{
    // Convert original arg to char
    char arg = arg_str.c_str()[1];

    // Display result
    std::cout << "char: " << arg << std::endl;
    std::cout << "int: " << static_cast<int>(arg) << std::endl;
    std::cout << "float: " << static_cast<float>(arg) << "f" << std::endl;
    std::cout << "double: " << static_cast<double>(arg) << std::endl;
}

void ScalarConverter::convertFromInt(const std::string& arg_str)
{
    long arg_long = 0;
  
    // Make streamstring to convert arg_str to long (to check overflow)
    std::stringstream arg_ss(arg_str);
    arg_ss >> arg_long;
    
    // Check overflow
    if (isOverflowInt(arg_long))
        return ;

    displayFromInt(arg_long);
}

void ScalarConverter::convertFromFloat(const std::string& arg_str)
{
    std::stringstream   arg_ss;
    std::string         arg_dup = arg_str;
    double              arg_double;

    // Check and handle special case (infinity/nanf)
    if (handleSpecialFloat(arg_str))
        return ;

    // Remove 'f' at the end of arg_str and convert arg to double
    arg_dup.erase(arg_dup.size() - 1);
    arg_ss << arg_dup;
    arg_ss >> arg_double;

    // Check overflow
    if (isOverflowFloat(arg_double))
        return ; 

    displayFromFloat(arg_double);
}

void ScalarConverter::convertFromDouble(const std::string& arg_str)
{
    std::stringstream   arg_ss(arg_str);
    long double         arg_double;

    arg_ss >> arg_double;

    // Check and handle special case (infinity/nan)
    if (handleSpecialDouble(arg_str))
        return ;

    // Check overflow
    if (isOverflowDouble(arg_double))
        return ;

    displayFromFloat(static_cast<double>(arg_double));
}

/*
** --------------------------------- Display -----------------------------------
*/
void ScalarConverter::displayFromInt(long nb)
{
    // Display char 
    if (isPrintable(nb))
        std::cout << "char: " << static_cast<char>(nb) << std::endl;
    else
        std::cout << "char: " << "Non displayable" << std::endl;

    // Display other type
    std::cout << "int: " << nb << std::endl;
    std::cout << "float: " << static_cast<float>(nb) << 'f' << std::endl;
    std::cout << "double: " << static_cast<double>(nb) << std::endl;
}

void ScalarConverter::displayFromFloat(double nb)
{
    // Display char 
    if (isPrintable(static_cast<long>(nb)))
        std::cout << "char: " << static_cast<char>(nb) << std::endl;
    else
        std::cout << "char: " << "Non displayable" << std::endl;

    // Display integer
    long arg_long = static_cast<long>(nb);
    if (arg_long > std::numeric_limits<int>::max() || arg_long < std::numeric_limits<int>::min())
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(nb) << std::endl;

    // Display floating numbers
    if (nb > std::numeric_limits<float>::max() || nb < std::numeric_limits<float>::min())
        std::cout << "float: impossible" << std::endl;
    else
        std::cout << "float: " << static_cast<float>(nb) << 'f' << std::endl;

    std::cout << "double: " << nb << std::endl;
}


/*
** ------------------------ Special Case Float/Double --------------------------
*/
bool ScalarConverter::handleSpecialFloat(const std::string& arg_str)
{
    float   arg_float;

    if (isSpecialCase(arg_str))
    {
        // Display char and integer (impossible)
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;

        // Display special case for float and double
        if (!arg_str.compare("+inff") || !arg_str.compare("-inff"))
        {
            arg_float = std::numeric_limits<float>::infinity();
            // Print a '-' if it is a negative infinity by checking first char of argument
            std::cout << "float: " << (arg_str[0] == '-' ? "-" : "") << arg_float << "f" << std::endl;
            std::cout << "double: " << (arg_str[0] == '-' ? "-" : "") << static_cast<double>(arg_float) << std::endl;
            return true;
        }
        if (!arg_str.compare("nanf"))
        {
            arg_float = std::numeric_limits<float>::quiet_NaN();
            std::cout << "float: " << arg_float << "f" << std::endl;
            std::cout << "double: " << static_cast<double>(arg_float) << std::endl;
            return true;
        }
    }
    return false;
}

bool ScalarConverter::handleSpecialDouble(const std::string& arg_str)
{
    double arg_double;

    if (isSpecialCase(arg_str))
    {
        // Display char and integer (impossible)
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;

        // Display special case for float and double
        if (!arg_str.compare("+inf") || !arg_str.compare("-inf"))
        {
            arg_double = std::numeric_limits<float>::infinity();
            // Print a '-' if it is a negative infinity by checking first char of argument
            std::cout   << "float: " << (arg_str[0] == '-' ? "-" : "") 
                        << static_cast<float>(arg_double) << 'f' << std::endl;
            std::cout << "double: " << (arg_str[0] == '-' ? "-" : "") << arg_double << std::endl;
            return true;
        }
        if (!arg_str.compare("nan"))
        {
            arg_double = std::numeric_limits<float>::quiet_NaN();
            std::cout << "float: " << static_cast<float>(arg_double) << 'f' << std::endl;
            std::cout << "double: " << arg_double << std::endl;
            return true;
        }
    }
    return false;
}

bool ScalarConverter::isSpecialCase(const std::string& str)
{
    if (!str.compare("+inff") || !str.compare("-inff") || !str.compare("nanf"))
        return true;
    if (!str.compare("+inf") || !str.compare("-inf") || !str.compare("nan"))
        return true;
    return false;
}

/*
** -------------------------- Small Helper Function ----------------------------
*/
bool ScalarConverter::isOverflowInt(long nb)
{
    if (nb > std::numeric_limits<int>::max() || nb < std::numeric_limits<int>::min())
    {
        std::cerr << "error: conversion of " << nb << " is impossible (underflow/overflow)\n";
        return true;
    }
    return false;
}

bool ScalarConverter::isOverflowFloat(double nb)
{
    if (nb > std::numeric_limits<float>::max() || nb < std::numeric_limits<float>::min())
    {
        std::cerr << "error: conversion of " << nb << " is impossible (underflow/overflow)\n";
        return true;
    }
    return false;
}

bool ScalarConverter::isOverflowDouble(long double nb)
{
    if (nb > std::numeric_limits<double>::max() || nb < std::numeric_limits<double>::min())
    {
        std::cerr << "error: conversion of " << nb << " is impossible (underflow/overflow)\n";
        return true;
    }
    return false;
}

bool ScalarConverter::isPrintable(long nb)
{
    if (nb > M_MIN_PRINTABLE && nb < M_MAX_PRINTABLE)
        return true;
    return false;
}