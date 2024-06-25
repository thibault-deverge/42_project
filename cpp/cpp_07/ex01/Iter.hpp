#pragma once

#include <iostream>

template <typename T, typename F>
void iter(T* array, int size, F* func)
{
    for (int i = 0; i < size; ++i)
        func(array[i]);
    std::cout << std::endl << std::endl;
}

template <typename T>
void printElements(T el)
{
    std::cout << el << " ";
}