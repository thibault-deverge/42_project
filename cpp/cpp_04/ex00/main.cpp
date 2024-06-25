#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
    std::cout << "---- BEGIN COPY TEST ----\n";
    Dog test;
    const Dog testcopy(test);
    std::cout << "---- END COPY TEST ----\n\n";

    std::cout << "---- BEGIN ANIMAL TEST ----\n";
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    std::cout << "----------\n";

    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;
    i->makeSound();
    j->makeSound();
    meta->makeSound();
    std::cout << "---- END ANIMAL TEST ----\n\n";
    
    std::cout << "---- BEGIN WRONG ANIMAL TEST ----\n";
    const WrongAnimal*  general = new WrongAnimal();
    const WrongAnimal*  k = new WrongCat();
    std::cout << "----------\n";

    std::cout << k->getType() << " " << std::endl;
    k->makeSound();
    meta->makeSound();
    std::cout << "---- END WRONG ANIMAL TEST ----\n";

    delete general;
    delete k;
    std::cout << "----------\n";
    delete meta;
    delete j;
    delete i;
    std::cout << "----------\n";
    return 0;
}