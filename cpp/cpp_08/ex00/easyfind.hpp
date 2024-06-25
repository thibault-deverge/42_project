#pragma once

#include <iostream>
#include <exception>
#include <algorithm>

template <typename T>
typename T::const_iterator easyfind(const T& collection, int value)
{
    typename T::const_iterator it; 
    
    it = std::find(collection.begin(), collection.end(), value);
    if (it == collection.end())
        throw std::runtime_error("Element doesn't exists in container ");
    return it;
}