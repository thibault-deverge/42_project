#pragma once

#include <iostream>
#include <exception>
#include <cstdlib>
#include <ctime>

class Base
{
private:

public:
    // Destructor
    virtual ~Base();

    // Member functions
    Base*   generate(void) const;
    void    identify(Base* p) const;
    void    identify(Base& p) const;

};