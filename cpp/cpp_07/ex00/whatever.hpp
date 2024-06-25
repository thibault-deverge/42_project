#pragma once

template <typename T>
void swap(T& nb1, T& nb2)
{
    T tmp =  nb1;
    nb1 = nb2;
    nb2 = tmp;
}

template <typename T>
const T& min(const T& nb1, const T& nb2)
{
    return (nb1 < nb2 ? nb1 : nb2);
}

template <typename T>
const T& max(const T& nb1, const T& nb2)
{
    return (nb1 > nb2 ? nb1 : nb2);
}