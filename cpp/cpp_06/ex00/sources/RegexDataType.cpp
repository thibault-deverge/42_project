#include "RegexDataType.hpp"

/*
** ------------------------------ REGEX Pattern --------------------------------
*/
const char* RegexDataType::M_PATTERN_CHAR      = "^'[^[:space:]]'$";
const char* RegexDataType::M_PATTERN_INT       = "^-?[[:digit:]]+$";
const char* RegexDataType::M_PATTERN_FLOAT     = "^-?[[:digit:]]+\\.[[:digit:]]*f$";
const char* RegexDataType::M_PATTERN_DOUBLE    = "^-?[[:digit:]]+\\.[[:digit:]]*$";

const char* RegexDataType::M_PATTERN_ARRAY[4] = {
    RegexDataType::M_PATTERN_CHAR,
    RegexDataType::M_PATTERN_INT,
    RegexDataType::M_PATTERN_FLOAT,
    RegexDataType::M_PATTERN_DOUBLE
};

/*
** ------------------------- Public Member functions ---------------------------
*/
int RegexDataType::findDataType(const std::string& arg)
{
    int code_regex = 0;

    // Loop over Regex pattern and check for data-type
    for (int i = 0; i < 4; ++i)
    {
        code_regex = searchRegexMatch(arg.c_str(), M_PATTERN_ARRAY[i]);
        if (code_regex == M_REGEX_FAIL)
            return M_REGEX_FAIL;
        if (code_regex == M_REGEX_SUCCESS)
            return i + 1;
    }

    // Check special pseudo litterals
    if (!arg.compare("-inff") || !arg.compare("+inff") || !arg.compare("nanf"))
        return M_FLOAT;
    if (!arg.compare("-inf") || !arg.compare("+inf") || !arg.compare("nan"))
        return M_DOUBLE;

    // Display error in case there is no match
    std::cerr << "error: " << arg << " is not a valid data-type. cannot convert\n";
    return M_REGEX_NOMATCH;
}

/*
** ---------------------------- Private functions ------------------------------
*/
int RegexDataType::searchRegexMatch(const char* arg, const char* pattern)
{
    regex_t regex;
    int     status;    
    char    msg_buf[100];

    // Compile regex to later on execute it
    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status)
    {
        regerror(status, &regex, msg_buf, sizeof(msg_buf));
        std::cerr << "Regex error: "  << msg_buf << std::endl;
        regfree(&regex);
        return M_REGEX_FAIL;
    }

    // Execute regex and check for errors
    status = regexec(&regex, arg, 0, NULL, 0);
    if (status && status != REG_NOMATCH)
    {
        regerror(status, &regex, msg_buf, sizeof(msg_buf));
        std::cerr << "Regex error: "  << msg_buf << std::endl;
        regfree(&regex);
        return M_REGEX_FAIL; 
    }

    // Check if there is a match
    regfree(&regex);
    if (status)
        return M_REGEX_NOMATCH;
    return M_REGEX_SUCCESS; 
}
