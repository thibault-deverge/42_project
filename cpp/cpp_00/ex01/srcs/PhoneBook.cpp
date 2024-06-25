#include "PhoneBook.hpp"

/*
 ---------- DEFAULT CONSTRUCTOR ----------
*/
PhoneBook::PhoneBook(): _contacts_size(0) {}

/*
 ---------- PRIVATES METHODS ----------
*/
void PhoneBook::displayHeaderContacts() const
{
    std::cout   << '|' << std::setw(10) << "id"
                << '|' << std::setw(10) << "first name"
                << '|' << std::setw(10) << "last name"
                << '|' << std::setw(10) << "nickname"
                << "|\n"; 
}

/*
 ---------- PUBLICS METHODS ----------
*/
void PhoneBook::welcomeMessage() const
{
    std::cout << "\n";
    std::cout << "==================================================\n";
    std::cout << "|                                                |\n";
    std::cout << "|            WELCOME TO YOUR PHONEBOOK           |\n";
    std::cout << "|                                                |\n";
    std::cout << "==================================================\n";
    std::cout << "\n";
}

void PhoneBook::displayInstruction() const
{
    std::cout << "\n-----------------------------------------\n";
    std::cout << "Here are some instructions to help you:\n";
    std::cout << "  * Enter 'ADD' to add a new contact.\n";
    std::cout << "  * Enter 'SEARCH' to display all contacts.\n";
    std::cout << "> ";
}

void PhoneBook::insertContact()
{
    // Check contact list is full - if yes, overwrite oldest one.
    if (_contacts_size == MAX_SIZE)
    {
        for (int idx = 0; idx < MAX_IDX; ++idx)
            _contacts[idx] = _contacts[idx + 1];
        _contacts[MAX_IDX].fillContact();
        return;
    }
    // If not - insert new contact.
    _contacts[_contacts_size].fillContact();
    ++_contacts_size;
}

void PhoneBook::displayPhoneBook() const
{
    displayHeaderContacts();
    for (int idx = _contacts_size - 1; idx >= 0; --idx)
    {
        _contacts[idx].displayContactSummary(idx + 1);
    }
    std::cout << std::endl;
}

void PhoneBook::searchContact() const
{
    int id = 0;

    do
    {
        std::cout << "Please enter the ID of the user you want to display information about (8 contacts maximum): ";
        std::cin >> id;
        // Check for EOF error if user enter ^D.
        if (std::cin.eof())
            throw std::invalid_argument(ERROR_EOF);
        // Clear error state of std::cin (ex: if string is entered by user).
        std::cin.clear();
        // Clear input buffer (ex: many value separed by space entered by user).
        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n');
    } while (id <= 0 || id > MAX_SIZE);

    if (_contacts[id - 1].isEmpty())
        std::cout << "\nSorry, this contact doesn't exists.\n";
    else
        _contacts[id - 1].displayContactFull(id);
}
