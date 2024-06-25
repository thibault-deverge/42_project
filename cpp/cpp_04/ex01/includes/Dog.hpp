#pragma once

#include <iostream>
#include <string>
#include "Animal.hpp"
#include "Brain.hpp"

class Dog: public Animal
{
private:
    Brain* m_brain;

    // Ban assignment operator
    Dog& operator=(const Dog& rhs);

public:
    // Constructors/Destructor
    Dog();
    Dog(const Dog& dog);
    ~Dog();

    // Member function
    void makeSound() const;
    void implementIdea(const std::string& value, int idx);

    // Accessers
    const std::string& getIdea(int idx);
};
