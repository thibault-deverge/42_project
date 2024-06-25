#include <iostream>
#include <string>

void    printArg(const std::string& arg)
{
    for (std::size_t i = 0; i < arg.size(); ++i)
        std::cout << static_cast<char>(std::toupper(arg[i]));
}

int     main(int argc, char *argv[])
{
    if (argc <= 1 || !argv[1][0])
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
    else
    {
        for (int i = 1; i < argc; ++i)
            printArg(argv[i]);
        std::cout << std::endl;
    }
    return 0;
}
