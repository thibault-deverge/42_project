#pragma once

#include <iostream>
#include <string>
#include <regex.h>

class RegexDataType
{
private:
    // Pattern REGEX
    static const char* M_PATTERN_ARRAY[4];
    static const char* M_PATTERN_CHAR;
    static const char* M_PATTERN_INT;
    static const char* M_PATTERN_FLOAT;
    static const char* M_PATTERN_DOUBLE;
    static const int   M_REGEX_SUCCESS = 1;
    static const int   M_REGEX_NOMATCH = 0;
    static const int   M_REGEX_FAIL    = -1;

    // Constructors / Destructor
    RegexDataType();
    RegexDataType(const RegexDataType& scalar);
    ~RegexDataType();

    // Assignment overload
    RegexDataType& operator=(const RegexDataType& rhs);

    // Private Functions
    static int searchRegexMatch(const char* arg, const char* pattern);

public:
    // Status code - Datatype
    static const int M_CHAR     = 1;
    static const int M_INT      = 2;
    static const int M_FLOAT    = 3;
    static const int M_DOUBLE   = 4;

    // Member functions
    static int findDataType(const std::string& arg);
};