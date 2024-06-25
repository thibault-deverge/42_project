#include "parsing.hpp"

// Constants
static const std::string ERR_NO_ARGS = "Error: The program expects argument(s) representing positive integers.";
static const std::string ERR_NON_DIGIT_ARGS = "Error: All arguments should be positive integers or sequences of digits.";
static const std::string ERR_OUT_OF_RANGE = "Error: The provided integer should be positive and not exceed size of integer.";
static const std::string ERR_ALREADY_SORTED = "Error: Input sequence passed as argument is already sorted.";

// Static prototypes
static bool is_digit(const std::string& arg);
static int convert_arg_to_int(const std::string& arg);
static bool is_already_sorted(const std::vector<int>& input_sequence);

/**
 * This function takes command-line arguments and populates a vector with integers
 * based on those arguments. It expects the arguments to be positive integers.
 */
bool parse_arguments(int argc, char** argv, std::vector<int>& input_sequence)
{
    if (argc < 2)
    {
        std::cout << ERR_NO_ARGS << std::endl;
        return false;
    }

    for (int i = 1; i < argc; ++i)
    {
        int value;

        if (!is_digit(argv[i]))
        {
            std::cout << ERR_NON_DIGIT_ARGS << std::endl;
            return false;
        }

        value = convert_arg_to_int(argv[i]);
        if (value == -1)
        {
            std::cout << ERR_OUT_OF_RANGE << std::endl;
            return false;
        }

        input_sequence.push_back(value);
    }

    if (is_already_sorted(input_sequence))
    {
        std::cout << ERR_ALREADY_SORTED << std::endl;
        return false;
    }

    return true;
}

static bool is_digit(const std::string& arg)
{
    std::string::const_iterator it = arg.begin();

    if (arg.empty())
        return false;

    if (*it == '+')
    {
        ++it;
        if (it == arg.end())
            return false;
    }

    while (it != arg.end())
    {
        if (!std::isdigit(*it))
            return false;
        ++it;
    }
    return true;
}

static int convert_arg_to_int(const std::string& arg)
{
    long value = std::strtol(arg.c_str(), NULL, 10);

    if (value < 0 || value > std::numeric_limits<int>::max())
        return -1;
    return static_cast<int>(value);
}

static bool is_already_sorted(const std::vector<int>& input_sequence)
{
    for (size_t i = 0; i < input_sequence.size() - 1; ++i)
    {
        if (input_sequence[i] > input_sequence[i + 1])
            return false;
    }
    return true;
}