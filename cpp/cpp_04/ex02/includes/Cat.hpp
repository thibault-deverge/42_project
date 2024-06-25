#pragma once

#include <iostream>
#include <string>
#include "A_Animal.hpp"
#include "Brain.hpp"

class Cat: public A_Animal
{
private:
    Brain* m_brain;

public:
    // Constructors/Destructor
    Cat();
    Cat(const Cat& cat);
    ~Cat();

    // Operator Overload
    Cat& operator=(const Cat& rhs);

    // Member function
    void makeSound() const;
    void implementIdea(const std::string& value, int idx);

    // Accessers
    const std::string& getIdea(int idx);
};