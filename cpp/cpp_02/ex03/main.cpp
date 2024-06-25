#include <iostream>
#include "Fixed.hpp"
#include "Point.hpp"

int main()
{
    try
    {
        // Try a point inside a triangle.
        Point v1(0.0f, 0.0f);
        Point v2(10.0f, 30.0f);
        Point v3(20.0f, 0.0f);
        Point pt(10.0f, 15.0f);
        Point copy(v3);

        std::cout << bsp(v1, v2, v3, pt) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}