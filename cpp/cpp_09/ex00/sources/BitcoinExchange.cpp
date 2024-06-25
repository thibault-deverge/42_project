#include "BitcoinExchange.hpp"

/*
** ----------------------- PARSING DATABASE INTO A MAP -------------------------
*/
std::map<std::string, double> BitcoinExchange::parseDatabase()
{
    Data_Map        database;
    std::ifstream   file(DB_NAME);
    std::string     line;

    if (!file.is_open() || file.fail())
        throw std::runtime_error(ERR_DATABASE);

    // verify first line is "date,exchange_rate"
    std::getline(file, line);
    if (!isMatchRegex(line, DB_HEADER_PATTERN))
        throw std::runtime_error(ERR_DATAENTRY);

    // fill database with each entry of the db_file
    while (std::getline(file, line))
        fillDbEntry(database, line);

    file.close();
    return database;
}

void BitcoinExchange::fillDbEntry(Data_Map& database, const std::string& line)
{
    std::istringstream  stream(line);
    std::string         date;
    double              value;

    // check format of the entry is "YEAR-MONTH-DATE,VALUE"
    if (!isMatchRegex(line, DB_ENTRY_PATTERN))
        throw std::invalid_argument(ERR_DATAENTRY);
    
    // check date is valid and exists
    std::getline(stream, date, ',');
    if (!isValidDate(date))
        throw std::invalid_argument(ERR_DATAENTRY);
    
    // check value of the entry is valid
    stream >> value;
    if (value > std::numeric_limits<int>::max())
        throw std::overflow_error(ERR_VALUE_OVERFLOW);
    if (value < 0)
        throw std::underflow_error(ERR_VALUE_UNDERFLOW);
    
    database[date] = value;
}

/*
** --------------------- PARSING INPUT AND DISPLAY VALUE -----------------------
*/
void BitcoinExchange::getValuesWallet(const Data_Map& database, const char* arg)
{
    std::ifstream   input_file(arg);
    std::string     line;

    if (!input_file.is_open() || input_file.fail())
        throw std::invalid_argument(ERR_FILE);

    // verify first line is "date|value"
    std::getline(input_file, line);
    if (!isMatchRegex(line, INPUT_HEADER_PATTERN))
        throw std::invalid_argument(ERR_HEADER);
    
    // loop through input file for each entry
    while (std::getline(input_file, line))
    {
        Input_Pair  input_line = parseLineInput(line);
        if (input_line.first == "NULL")
            continue;
        displayLine(database, input_line.first, input_line.second);
    }
}

Input_Pair BitcoinExchange::parseLineInput(const std::string& line)
{
    Input_Pair          key_value;
    std::istringstream  stream(line);
    std::string         date;
    double              value;

    // Initialize pair key to "NULL" to return it in case of error
    key_value.first = "NULL";

    // check format of the entry is "YEAR-MONTH-DATE | VALUE"
    std::getline(stream, date, '|');
    if (!isMatchRegex(line, INPUT_ENTRY_PATTERN) || !isValidDate(date))
    {
        std::cerr << "Error: bad input => " << date << std::endl;
        return key_value;
    }

    stream >> value;
    if (!isValidValue(value))
        return key_value;
    
    // Update key/value pair and return it if line is valid
    key_value.first = date;
    key_value.second = value;
    return key_value;
}

void BitcoinExchange::displayLine(const Data_Map& database, const std::string& date, double value)
{
    // return first iterator not less than the date we are searching
    std::map<std::string, double>::const_iterator it = database.lower_bound(date);
    
    // Handle case it founds exact same date or not
    if (date != it->first)
    {
        // return error if no date were equivalent or before date we are searching
        if (it != database.begin())
        {
            --it;
            std::cout << date << "=> " << value << " = ";
            std::cout << it->second * value << std::endl;
        }
        else
            std::cerr << "Error: " << date << " have no corresponding entry.\n";
    }
    else
    {
        std::cout << date << "=> " << value << " = ";
        std::cout << it->second * value << std::endl;
    }
}

/*
** ------------------------- HELPER MEMBER FUNCTIONS ---------------------------
*/
bool BitcoinExchange::isValidDate(const std::string& date)
{
    std::istringstream      stream_date(date);
    std::string             token;
    int                     results[3];
    int                     i = 0;

    while (std::getline(stream_date, token, '-'))
        results[i++] = atoi(token.c_str());

    int year    = results[0];
    int month   = results[1];
    int day     = results[2];

    if (year < CREATION_BTC_YEAR || year > CURRENT_YEAR)
        return false;
    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > 31)
        return false;

    if (month == 2)
    {
        if (isLeapYear(year))
            return day <= 29;
        return day <= 28;
    }

    if (month == 4 || month == 6 || month == 9 || month == 11)
        return day <= 30;

    return true;
}

bool BitcoinExchange::isMatchRegex(const std::string& line, const char* pattern)
{
    regex_t    regex;
    int        status;

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status)
    {
        regfree(&regex);
        return false;
    }
    
    status = regexec(&regex, line.c_str(), 0, NULL, 0);
    if (status == REG_NOMATCH)
    {
        regfree(&regex);
        return false;
    }
    regfree(&regex);
    return true;
}

bool BitcoinExchange::isValidValue(double value)
{
    if (value > std::numeric_limits<int>::max() || value < 0)
    {
        if (value < 0)
            std::cerr << "Error: not a positive number.\n";
        else
            std::cerr << "Error: too large a number.\n";
        return false;
    }
    return true;
}

bool BitcoinExchange::isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}