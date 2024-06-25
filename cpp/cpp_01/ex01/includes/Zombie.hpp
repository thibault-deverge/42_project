#pragma once

#include <iostream>
#include <string>

class Zombie
{
private:
    static const std::string DEFAULT_NAME;

    std::string _name;

public:
    Zombie();
    Zombie(std::string name);  
    ~Zombie();

    const std::string&  getName() const;
    void                setName(std::string name);

    void    announce();
};

Zombie* zombieHorde(int N, std::string name);