#pragma once

#include <string>

class Weapon
{
private:
    static const std::string DEFAULT_WEAPON;

    std::string _type;

public:
    Weapon();
    Weapon(const std::string& type);

    const std::string&  getType() const;
    void                setType(const std::string& type); 
};