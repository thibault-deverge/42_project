#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <sstream>
#include <limits>
#include <stack>
#include <cstdlib>

class RPN
{
private:
    // Error messages
    static const std::string ERR_DIGIT_FORMAT;
    static const std::string ERR_OPERATOR_FORMAT;
    static const std::string ERR_DIGIT_RANGE;
    static const std::string ERR_ARGS_FORMAT;
    static const std::string ERR_DIVISION_0;
    static const std::string ERR_OVERFLOW;
    static const std::string ERR_UNDERFLOW;
    static const std::string ERR_NB_OPERATORS;

    // Member variable
    std::stack<int> _operands;

    // Parsing functions
    void parse_digit(const std::string& arg);
    bool is_operator(const std::string& arg) const;

    // Calculation functions
    void find_operator(const std::string& arg);
    void add(int nb1, int nb2);
    void substract(int nb1, int nb2);
    void multiply(int nb1, int nb2);
    void divide(int nb1, int nb2);

public:
    // Constructors / Destructor
    RPN();
    RPN(const RPN& rpn);
    ~RPN();

    // Assignment overload
    RPN& operator=(const RPN& rhs);

    // Public Member function
    void calculate(const char *argv);

};