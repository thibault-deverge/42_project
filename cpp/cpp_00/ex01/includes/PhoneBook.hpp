#pragma once

#include <iostream>
#include <string>
#include "Contact.hpp"

class PhoneBook
{
private:
    static const int MAX_SIZE = 8;
    static const int MAX_IDX = MAX_SIZE - 1;

    Contact _contacts[PhoneBook::MAX_SIZE];
    int     _contacts_size;

    void displayHeaderContacts() const;

public:
    PhoneBook();

    void welcomeMessage() const;
    void displayInstruction() const;
    void displayPhoneBook() const; 
    void searchContact() const;
    void insertContact();
};
