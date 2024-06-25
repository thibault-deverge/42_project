#pragma once

#include <iostream>
#include <string>

class Animal
{
private:
    // Operator Overload
    Animal& operator=(const Animal& rhs);

protected:
    // Parameterized constructor
    Animal(const std::string& type);

    // Type of animal
    const std::string m_type;

public:
    // Constructors/Destructor
    Animal();
    Animal(const Animal& animal);
    virtual ~Animal();

    // Member function
    virtual void makeSound() const;

    // Accessers
    const std::string&  getType() const;
};