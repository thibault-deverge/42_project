#pragma once

#include <stack>
#include <deque>

template <typename T, typename container = std::deque<T> >
class MutantStack: public std::stack<T, container>
{
public:
    // Constructors / destructor
    MutantStack(): std::stack<T>() {}
    MutantStack(const MutantStack<T>& other): std::stack<T>(other)  {}
    ~MutantStack() {}

    // Assignment overload
    MutantStack<T>& operator=(const MutantStack& rhs)
    {
        if (this != &rhs)
           std::stack<T>::operator=(rhs);
        return *this;
    }

    // Iterateur
    typedef typename container::iterator iterator;

    iterator  begin() 
    {
        return this->c.begin();
    }

    iterator  end() 
    {
        return this->c.end();
    }
};