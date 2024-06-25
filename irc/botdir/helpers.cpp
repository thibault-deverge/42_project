#include "../includes/Bot.hpp"

int parse_arguments(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cerr << ERROR_NB_ARGUMENTS << std::endl;
		return PARSING_ERROR;
	}

	int port = parse_port(argv[1]);
	if (port == PARSING_ERROR)
		return PARSING_ERROR;

	if (!parse_password(argv[3]))
		return PARSING_ERROR;
	return port;
}

int parse_port(const std::string& port_str)
{
	std::istringstream  iss(port_str);
	int                 port;

	if (!(iss >> port) || !iss.eof())
	{
		std::cerr << ERROR_PORT_VALIDITY;
		return PARSING_ERROR;
	}

	if (port < MIN_PORT || port > MAX_PORT)
	{
		std::cerr << ERROR_PORT_RANGE;
		return PARSING_ERROR;
	}
	return port;
}

bool parse_password(const std::string& password)
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

std::string find_and_replace(const std::string &error, const char *find, const char *replace)
{
	if (!find || !replace)
		return error;
	std::string new_error = error;
	std::string find_str(static_cast<std::string>("<") + static_cast<std::string>(find) + static_cast<std::string>(">"));
	new_error.replace(error.find(find_str), find_str.size(), replace);
	return (new_error);
}

bool	test_path_regex(const char *pat, const char *str)
{
	regex_t regex;

	if (regcomp(&regex, pat, REG_EXTENDED) != 0)
		throw(std::logic_error("Error with the regex compilation"));
	if (regexec(&regex, str, 0, NULL, 0) == 0)
	{
		regfree(&regex);
		return (true);
	}
	else
	{
		regfree(&regex);
		return (false);
	}
}
