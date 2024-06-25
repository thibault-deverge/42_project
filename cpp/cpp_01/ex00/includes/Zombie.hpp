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

    void    announce(void);
};

Zombie* newZombie( std::string name );
void    randomChump( std::string name );