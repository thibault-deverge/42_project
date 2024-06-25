#pragma once

#include <iostream>
#include <string>
#include "A_Animal.hpp"
#include "Brain.hpp"

class Dog: public A_Animal
{
private:
    Brain* m_brain;

public:
    // Constructors/Destructor
    Dog();
    Dog(const Dog& dog);
    ~Dog();

    // Operator Overload
    Dog& operator=(const Dog& rhs);

    // Member function
    void makeSound() const;
    void implementIdea(const std::string& value, int idx);

    // Accessers
    const std::string& getIdea(int idx);
};
