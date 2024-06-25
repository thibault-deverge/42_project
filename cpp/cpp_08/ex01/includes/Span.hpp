#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <limits>
#include <cstdlib>
#include <unistd.h>


class Span
{
private:
    typedef std::vector<int>::iterator          vector_it;
    typedef std::vector<int>::const_iterator    const_vector_it;

    static const int M_DEFAULT_CAPACITY = 16;

    std::vector<int>  m_data;

public:
    // Static variable
    static const int DEFAULT_RANGE_RD = 100000;

    // Constructors / destructor
    Span();
    Span(int n);
    Span(const Span& other);
    ~Span();

    // Assignment
    Span& operator=(const Span& rhs);

    // Add numbers to vector
    void addNumber(int n);
    void addNumbers(vector_it begin, vector_it end);

    // Find span
    int shortestSpan() const;
    int longestSpan() const;

    // Helper function
    void printData() const;
};