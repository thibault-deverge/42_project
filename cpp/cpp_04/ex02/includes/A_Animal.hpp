#pragma once

#include <iostream>
#include <string>

class A_Animal
{
private:
    // Constructors
    A_Animal();
    A_Animal(const A_Animal& animal);

    // Operator overload
    A_Animal& operator=(const A_Animal& rhs);

protected:
    // Constructors
    A_Animal(const std::string& type);

    const std::string m_type;

public:
    // Destructor
    virtual ~A_Animal();

    // Member function
    virtual void makeSound() const = 0;

    // Accessors
    const std::string&  getType() const;
};