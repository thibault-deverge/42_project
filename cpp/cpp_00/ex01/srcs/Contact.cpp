#include "Contact.hpp"

/*
 ---------- DEFAULT CONSTRUCTOR ----------
*/
Contact::Contact(){}

/*
 ---------- PRIVATES METHODS ----------
*/
std::string Contact::truncateStr(std::string str, size_t width) const
{
    if (str.length() > width)
        return str.substr(0, width - 1) + '.';
    else
        return str;
}

void Contact::print_aligned(const std::string& label, const std::string& value) const
{
    std::cout   << std::setw(Contact::BLOCK_SIZE) << std::left
                << label << value << std::endl;
}

/*
 ---------- PUBLICS METHODS ----------
*/
bool Contact::isEmpty() const
{
    if (_first_name.empty())
        return true;
    return false;
}

void Contact::displayContactSummary(int id) const
{
    if (!_first_name.empty())
    {
        std::cout   << '|' << std::setw(10) << id
                    << '|' << std::setw(10) << truncateStr(_first_name, 10)
                    << '|' << std::setw(10) << truncateStr(_last_name, 10)
                    << '|' << std::setw(10) << truncateStr(_nickname, 10)
                    << "|\n";
    }
}

void Contact::displayContactFull(int id) const
{
    std::cout   << std::setw(Contact::BLOCK_SIZE) << std::left << "ID: " << id << '\n';
    print_aligned("First name: ", _first_name); 
    print_aligned("Last name: ", _last_name); 
    print_aligned("Nickname: ", _nickname); 
    print_aligned("Phone number: ", _phone_number); 
    print_aligned("Darkest secret: ", _darkest_secret); 
}

void Contact::fillContact()
{
    std::cout << "First name: > ";
    while (!std::getline(std::cin >> std::ws, _first_name))
        throw std::invalid_argument(ERROR_EOF);

    std::cout << "Last name: > ";
    if (!std::getline(std::cin >> std::ws, _last_name))
        throw std::invalid_argument(ERROR_EOF);

    std::cout << "Nickname: > ";
    if (!std::getline(std::cin >> std::ws, _nickname))
        throw std::invalid_argument(ERROR_EOF);

    std::cout << "Phone Number: > ";
    if (!std::getline(std::cin >> std::ws, _phone_number))
        throw std::invalid_argument(ERROR_EOF);

    std::cout << "Darkest secret: > ";
    if (!std::getline(std::cin >> std::ws, _darkest_secret))
        throw std::invalid_argument(ERROR_EOF);
}