#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <map>
#include <cstdlib>
#include <regex.h>
#include "appConstants.hpp"

typedef std::map<std::string, double> Data_Map;
typedef std::pair<std::string, double> Input_Pair;

class BitcoinExchange
{
private:
    // Coplien's form (private as static class are not instanciables)
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    ~BitcoinExchange();
    BitcoinExchange& operator=(const BitcoinExchange& rhs);

    // Fills a map with exchange rate data parsed from a line of database.
    static void fillDbEntry(Data_Map& database, const std::string& line);

    // Parses a line of input to extract the date and value and output result.
    static Input_Pair parseLineInput(const std::string& line);
    static void displayLine(const Data_Map& database, const std::string& date, double value);

    // Helper functions for input validation and regex matching.
    static bool isMatchRegex(const std::string& line, const char* pattern);
    static bool isValidDate(const std::string& date);
    static bool isLeapYear(int year);
    static bool isValidValue(double value);

public:
    // Parses the database into a map of date-exchange rate pairs.
    static Data_Map parseDatabase();

    // Calculates and displays the value of a wallet based on historical Bitcoin exchange rates.
    static void getValuesWallet(const Data_Map& database, const char* arg);
};