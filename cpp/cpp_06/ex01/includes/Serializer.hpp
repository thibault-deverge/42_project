#pragma once

#include <stdint.h>
#include "Data.hpp"

class Serializer
{
private:
    // Constructors / Destructor
    Serializer();
    Serializer(const Serializer& serializer);
    ~Serializer();

    // Assignment overload
    Serializer& operator=(const Serializer& rhs);

public:
    // Member functions
    static uintptr_t    serialize(Data* ptr);
    static Data*        deserialize(uintptr_t raw);
};