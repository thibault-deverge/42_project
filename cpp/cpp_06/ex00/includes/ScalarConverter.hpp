#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>
#include "RegexDataType.hpp"

class ScalarConverter
{
private:
    static const int   M_REGEX_NOMATCH = 0;
    static const int   M_REGEX_FAIL    = -1;
    static const int   M_MIN_PRINTABLE = 32;
    static const int   M_MAX_PRINTABLE = 126;

    // Constructors / Destructor
    ScalarConverter();
    ScalarConverter(const ScalarConverter& scalar);
    ~ScalarConverter();

    // Assignment overload
    ScalarConverter& operator=(const ScalarConverter& rhs);

    // Convert functions
    static void convertFromChar(const std::string& arg);
    static void convertFromInt(const std::string& arg);
    static void convertFromFloat(const std::string& arg);
    static void convertFromDouble(const std::string& arg_str);

    // Infinity/Nan
    static bool handleSpecialFloat(const std::string& arg_str);
    static bool handleSpecialDouble(const std::string& arg_str);

    // Display
    static void displayFromFloat(double nb);
    static void displayFromInt(long nb);

    // Small helper functions
    static bool isOverflowInt(long nb);
    static bool isOverflowFloat(double nb);
    static bool isOverflowDouble(long double nb);
    static bool isPrintable(long nb);
    static bool isSpecialCase(const std::string& str);

public:
    // Member functions
    static void convert(const std::string& arg);
};