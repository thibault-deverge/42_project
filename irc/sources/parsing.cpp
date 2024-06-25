#include "parsing.hpp"

static int  parse_port(const std::string& port_str);
static bool parse_password(const std::string& password);

int parse_arguments(int argc, char **argv)
{
    // Verify the correct number of arguments
    if (argc != 3)
    {
        std::cerr << ERROR_NB_ARGUMENTS << std::endl;
        return PARSING_ERROR;
    }

    // Parse and validate port number
    int port = parse_port(argv[1]);
    if (port == PARSING_ERROR)
        return PARSING_ERROR;

    // Validate password
    if (!parse_password(argv[2]))
        return PARSING_ERROR;

    return port;
} 

static int parse_port(const std::string& port_str)
{
    std::istringstream  iss(port_str);
    int                 port;

    // Check if port is a valid integer and consume the entire input
    if (!(iss >> port) || !iss.eof())
    {
        std::cerr << ERROR_PORT_VALIDITY;
        return PARSING_ERROR;
    }

    // Check if port is within the specified range
    if (port < MIN_PORT || port > MAX_PORT)
    {
        std::cerr << ERROR_PORT_RANGE;
        return PARSING_ERROR;
    }
    return port;
}

static bool parse_password(const std::string& password)
{
    size_t password_len = password.size();

    // Check password length constraints (4 to 12 characters)
    if (password_len < 4 || password_len > 12)
    {
        std::cerr << ERROR_PASSWORD << std::endl;
        return false;
    }
    return true;
}