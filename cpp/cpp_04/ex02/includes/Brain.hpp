#pragma once

#include <iostream>
#include <string>

class Brain
{
private:
    static const int m_size_array = 100;

    std::string m_ideas[Brain::m_size_array];

public:
    // Constructors/Destructor
    Brain();
    Brain(const Brain& brain);
    ~Brain();

    // Operator overload
    Brain& operator=(const Brain& brain);

    // Member Functions
    void fillIdea(std::string value, int idx);
    const std::string& getIdea(int idx);
};