#include "PhoneBook.hpp"
#include "Contact.hpp"

int     main()
{
    PhoneBook   phoneBook;
    std::string input;

    phoneBook.welcomeMessage();
    try
    {
        do
        {
            phoneBook.displayInstruction();

            // Check for EOF error if user enter ^D.
            if (!std::getline(std::cin, input))
                throw std::invalid_argument(ERROR_EOF);
            if (input == "ADD")
                    phoneBook.insertContact();
            else if (input == "SEARCH")
            {
                phoneBook.displayPhoneBook();
                phoneBook.searchContact();
            }
        } while (input != "EXIT");
    }
    catch(const std::invalid_argument& error)
    {
        std::cerr << error.what() << std::endl;
        return 1;
    }
    return 0;
}