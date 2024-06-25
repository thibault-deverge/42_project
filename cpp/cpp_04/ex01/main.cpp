#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
    const int     size_array = 10;
    
    std:: cout << "------ CREATION POINTERS ------\n";
    const Animal* j = new Dog();
    const Animal* i = new Cat();


    std::cout << "----- CREATION COPY BEGIN -------\n";
    Dog dog;
    dog.implementIdea("pissed of the cat", 3);
    Dog dog2(dog);
    std::cout << dog2.getIdea(3);


    std::cout << "----- CREATION ARRAY BEGIN -------\n";
    Animal* animals[size_array];
    for (int i = 0; i < size_array / 2; ++i)
        animals[i] = new Dog();
    for (int i = size_array / 2; i < size_array; ++i)
        animals[i] = new Cat();
    (void)animals;


    std::cout << "----- DESTRUCTION ARRAY BEGIN -------\n";
    for (int i = 0; i < size_array / 2; ++i)
        delete animals[i];
    for (int i = size_array / 2; i < size_array; ++i)
        delete animals[i];

    std::cout << "------ DESTRUCTION POINTERS ------\n";
    delete j;
    delete i;

    std::cout << "------ DESTRUCTION STATIC ------\n";
    return 0;
}