#pragma once

#include <iostream>
#include <string>
#include "Animal.hpp"

class Cat: public Animal
{
private:
    // Operator Overload
    Cat& operator=(const Cat& rhs);

public:
    // Constructors/Destructor
    Cat();
    Cat(const Cat& cat);
    ~Cat();

    // Member function
    void makeSound() const;
};