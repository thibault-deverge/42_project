#pragma once

#include <iostream>
#include <string>
#include "Animal.hpp"

class Dog: public Animal
{
private:
    // Operator Overload
    Dog& operator=(const Dog& rhs);

public:
    // Constructors/Destructor
    Dog();
    Dog(const Dog& dog);
    ~Dog();

    // Member function
    void makeSound() const;
};
