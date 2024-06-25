#pragma once

#include <iostream>
#include <string>

class WrongAnimal
{
private:
    // Ban assignment operator
    WrongAnimal& operator=(const WrongAnimal& rhs);

protected:
    // Parameterized constructor
    WrongAnimal(const std::string& type);

    const std::string m_type;

public:
    // Constructors/Destructor
    WrongAnimal();
    WrongAnimal(const WrongAnimal& animal);
    virtual ~WrongAnimal();

    // Member function
    void makeSound() const;

    // Accessers
    const std::string&  getType() const;
};