#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "easyfind.hpp"

int main()
{
    /*
    ** TEST WITH VECTOR CONTAINER 
    */
    std::cout << "---------- VECTOR ----------\n";
    std::vector<int> my_vector;
    for (int i = 1; i <= 10; ++i)
        my_vector.push_back(i);

    try {
        std::cout << *easyfind(my_vector, 4) << std::endl;
        std::cout << *easyfind(my_vector, 18) << std::endl;
    }
    catch(const std::exception& e){
        std::cerr << "exception: " << e.what() << "vector." << '\n';
    }
    std::cout << std::endl;

    /*
    ** TEST WITH LIST CONTAINER 
    */
    std::cout << "---------- LIST ----------\n";
    std::list<int> my_list;
    for (int i = 1; i <= 10; ++i)
        my_list.push_back(i);

    try {
        std::cout << *easyfind(my_list, 5) << std::endl;
        std::cout << *easyfind(my_list, 13) << std::endl;
    }
    catch(const std::exception& e){
        std::cerr << "exception: " << e.what() << "list." << '\n';
    }
    std::cout << std::endl;

    /*
    ** TEST WITH DEQUE CONTAINER 
    */
    std::cout << "---------- DEQUE ----------\n";
    std::deque<int> my_deque;
    for (int i = 1; i <= 10; ++i)
        my_deque.push_back(i);

    try {
        std::cout << *easyfind(my_deque, 8) << std::endl;
        std::cout << *easyfind(my_deque, 15) << std::endl;
    }
    catch(const std::exception& e){
        std::cerr << "exception: " << e.what() << "deque." << '\n';
    }
    std::cout << std::endl;

    return 0;
}