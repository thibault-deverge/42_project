#pragma once

#include <iostream>
#include <string>
#include "Animal.hpp"
#include "Brain.hpp"

class Cat: public Animal
{
private:
    Brain* m_brain;

    // Ban assignment operator
    Cat& operator=(const Cat& rhs);

public:
    // Constructors/Destructor
    Cat();
    Cat(const Cat& cat);
    ~Cat();

    // Member function
    void makeSound() const;
    void implementIdea(const std::string& value, int idx);

    // Accessers
    const std::string& getIdea(int idx);
};