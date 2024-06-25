
#pragma once

#include <iostream>
#include <string>
#include "WrongAnimal.hpp"

class WrongCat: public WrongAnimal
{
private:
    // Ban assignment operator
    WrongCat& operator=(const WrongCat& rhs);

public:
    // Constructors/Destructor
    WrongCat();
    WrongCat(const WrongCat& cat);
    ~WrongCat();

    // Member function
    void makeSound() const;
};