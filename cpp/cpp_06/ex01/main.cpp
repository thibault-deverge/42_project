#include <iostream>
#include "Serializer.hpp"

int main()
{
    Data data;
    uintptr_t data_int;
    
    std::cout << "Original Data: " << &data << std::endl;

    data_int = Serializer::serialize(&data);
    std::cout << "Data serialize: " << data_int << std::endl;
    std::cout << "Data deserialize: " << Serializer::deserialize(data_int) << std::endl;

    return 0;
}