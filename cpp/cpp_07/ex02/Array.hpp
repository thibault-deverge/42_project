#pragma once

#include <exception>

template<typename T>
class Array
{
private:
    T*              m_array;
    unsigned int    m_size;

public:
    // Constructors / Destructor
    Array();
    Array(unsigned int n);
    Array(const Array& arr);
    ~Array();

    // Assignment overload
    Array& operator=(const Array& rhs);

    // Subscript overload (a faire)
    T& operator[](unsigned int index);
    const T& operator[](unsigned int index) const;

    // Member functions
    unsigned int size() const;
    void print() const;
};

#include "Array.tpp"