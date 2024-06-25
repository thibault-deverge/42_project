#include "RPN.hpp"

/*
** ------------------------- Static Private Variable --------------------------
*/
const std::string RPN::ERR_DIGIT_FORMAT     = "digit is not valid.";
const std::string RPN::ERR_OPERATOR_FORMAT  = "operator is not valid.";
const std::string RPN::ERR_DIGIT_RANGE      = "RPN only accept single-digit operands.";
const std::string RPN::ERR_ARGS_FORMAT      = "Insufficient operands to perform the operation.";
const std::string RPN::ERR_DIVISION_0       = "Cannot divide by 0.";
const std::string RPN::ERR_OVERFLOW         = "Operation resulted in overflow; exceeds INT_MAX.";
const std::string RPN::ERR_UNDERFLOW        = "Operation resulted in underflow; falls below INT_MIN.";
const std::string RPN::ERR_NB_OPERATORS     = "Excess operands without corresponding operators.";

/*
** ------------------------- Public Member Functions ---------------------------
*/
// Constructors / Destructor
RPN::RPN() {}
RPN::RPN(const RPN& rpn) { _operands = rpn._operands; }
RPN::~RPN() {}

// Assignment overload
RPN& RPN::operator=(const RPN& rhs)
{
    if (this != &rhs)
        _operands = rhs._operands;
    return *this;
}

// Main function (launch the calculation)
void RPN::calculate(const char *args)
{
    std::string         arguments = args;
    std::istringstream  arg_stream(arguments);
    std::string         arg;
    
    while (getline(arg_stream, arg, ' '))
    {
        // Continue if multiple space between arguments to skip them    
        if (arg.empty())
            continue;
        
        // Perform operation if arg is operator or add to stack if digit
        if (is_operator(arg))
            find_operator(arg);
        else
            parse_digit(arg);
    } 
    // throw error if there are too much numbers compared to operator
    if (_operands.size() > 1)
        throw std::invalid_argument(ERR_NB_OPERATORS);
    
    // display result
    std::cout << _operands.top() << std::endl;
}

/*
** ------------------------- Operations Functions -----------------------------
*/
// Operations functions
void RPN::find_operator(const std::string& arg)
{
    if (_operands.size() < 2)
        throw std::invalid_argument(ERR_ARGS_FORMAT);
    
    int second_number = _operands.top();
    _operands.pop();
    int first_number = _operands.top();
    _operands.pop();

    if (arg == "+")
        add(first_number, second_number);
    else if (arg == "-")
        substract(first_number, second_number);
    else if (arg == "*")
        multiply(first_number, second_number);
    else 
        divide(first_number, second_number);
}

void RPN::add(int nb1, int nb2)
{
    long result = static_cast<long>(nb1) + nb2;
    if (result > std::numeric_limits<int>::max())
        throw std::overflow_error(ERR_OVERFLOW);

    _operands.push(result);
}

void RPN::substract(int nb1, int nb2)
{
    long result = static_cast<long>(nb1) - nb2;
    if (result < std::numeric_limits<int>::min())
        throw std::underflow_error(ERR_UNDERFLOW);

    _operands.push(result);
}

void RPN::multiply(int nb1, int nb2)
{
    long result = static_cast<long>(nb1) * nb2;
    if (result > std::numeric_limits<int>::max())
        throw std::overflow_error(ERR_OVERFLOW);

    _operands.push(result);
}

void RPN::divide(int nb1, int nb2)
{
    if (nb2 == 0)
        throw std::invalid_argument(ERR_DIVISION_0);
    _operands.push(nb1 / nb2);
}

/*
** --------------------------- Parsing Functions -------------------------------
*/
void RPN::parse_digit(const std::string& arg)
{
    for (size_t i = 0; i < arg.size(); ++i)
    {
        if (!isdigit(arg[i]))
            throw std::invalid_argument(ERR_DIGIT_FORMAT);
    }

    int num = std::atoi(arg.c_str());
    
    // throw error if conversion can't be performed
    if (num == 0 && arg != "0")
        throw std::invalid_argument(ERR_DIGIT_FORMAT);

    // throw error if not in range [0-9]
    if (num < 0 || num > 9)
        throw std::invalid_argument(ERR_DIGIT_RANGE);
    
    _operands.push(num);
}

bool RPN::is_operator(const std::string& arg) const
{
    if  (arg[0] == '+' || arg[0] == '-' || arg[0] == '*' || arg[0] == '/')
    {
        if (arg.size() == 1)
            return true;
        throw std::invalid_argument(ERR_OPERATOR_FORMAT);
        return false;
    }
    return false;
}