#pragma once

#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <iomanip>

const std::string   ERROR_EOF = "\nerror: canno't handle EOF as input.";

class Contact
{
private:
    static const int BLOCK_SIZE = 20;

    std::string _first_name;
    std::string _last_name;
    std::string _nickname;
    std::string _phone_number;
    std::string _darkest_secret;

    std::string truncateStr(std::string str, size_t width) const;
    void print_aligned(const std::string& label, const std::string& value) const;

public:
    Contact();

    bool isEmpty() const;
    void displayContactSummary(int id) const;
    void displayContactFull(int id) const;
    void fillContact();
};
