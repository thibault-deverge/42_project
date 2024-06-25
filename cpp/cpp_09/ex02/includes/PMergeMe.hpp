#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <algorithm>
#include <vector>
#include <deque>
#include <sys/time.h>

class PMergeMe
{
protected:
    // Typedef
    typedef std::deque< std::pair<int, int> >   Pair_Deque;
    typedef std::vector< std::pair<int, int> >  Pair_Vector;

    typedef std::pair<int,int>  Int_Pair;
    typedef std::vector<int>    Int_Vector; 
    typedef std::deque<int>     Int_Deque;

    // Member variables
    int             _input_size;
    int             _single_odd_element;
    Int_Vector      _fjohnson_sequence;
    struct timeval  _start, _end;

    // Coplien's form
    PMergeMe();
    PMergeMe(const PMergeMe& other);
    virtual ~PMergeMe();
    PMergeMe& operator=(const PMergeMe& rhs);

    // General member functions
    void generate_fjohnson_sequence();

public:
    void print_unsorted_elements(const Int_Vector& input_sequence) const;   
    void print_time_to_process(const std::string& container) const;

    // Pure virtual function
    virtual void fjohnson_algorithm(const Int_Vector&) = 0;
    virtual void print_sorted_elements() const = 0;
};