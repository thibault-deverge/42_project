#include <iostream>
#include "A_Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
    /*
     * Uncomment next lime will throw error at compilation because
     * it is now an abstract class and can't be instantiate.
    */
    //A_Animal* animal = new A_Animal();
    A_Animal* dog = new Dog();
    A_Animal* cat = new Cat();

    std::cout << dog->getType() << std::endl;
    std::cout << cat->getType() << std::endl;

    dog->makeSound();
    cat->makeSound();

    delete dog;
    delete cat;
    return 0;
}