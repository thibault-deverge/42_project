#pragma once

#include <string>

// Error Messages
static const std::string ERR_FILE               = "could not open file.";
static const std::string ERR_DATABASE           = "could not open database.";
static const std::string ERR_DATAENTRY          = "database is not valid.";
static const std::string ERR_INPUT_FILE         = "input file is not valid.";
static const std::string ERR_VALUE_OVERFLOW     = "value is not valid.";
static const std::string ERR_VALUE_UNDERFLOW    = "value is not positive.";
static const std::string ERR_ARGS               = "too many arguments.";
static const std::string ERR_HEADER             = "header of input file is invalid.";

// Regex Pattern
static const char* DB_NAME = "ressources/data.csv";
static const char* DB_HEADER_PATTERN = "^\\s*date,exchange_rate\\s*$";
static const char* DB_ENTRY_PATTERN = "^[0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9],[0-9]*\\.?[0-9]*$";
static const char* INPUT_HEADER_PATTERN = "^(\\s*[Dd][Aa][Tt][Ee]\\s\\|\\s[Vv][Aa][Ll][Uu][Ee]\\s*)$";
static const char* INPUT_ENTRY_PATTERN = "^[0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9] | [0-9]*\\.?[0-9]*$";

// Utils
static const int CREATION_BTC_YEAR = 2009;
static const int CURRENT_YEAR = 2024;