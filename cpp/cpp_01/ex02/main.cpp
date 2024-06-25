#include <iostream>
#include <string>

int main()
{
    // Initialize string, pointer and reference variables
    std::string     stringVAR = "HI THIS IS BRAIN";
    std::string*    stringPTR = &stringVAR;
    std::string&    stringREF = stringVAR;

    // Print memory address
    std::cout << &stringVAR << std::endl;
    std::cout << stringPTR << std::endl;
    std::cout << &stringREF << std::endl;

    // Print value
    std::cout << stringVAR << std::endl;
    std::cout << *stringPTR << std::endl;
    std::cout << stringREF << std::endl;

    return 0;
}