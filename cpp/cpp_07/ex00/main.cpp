#include <iostream>
#include "whatever.hpp"

int main()
{
    /*
    ** ----- INTEGER ----- 
    */
    int a = 2;
    int b = 3;
    
    // Swap operation
    std::cout << "Before swap: a = " << a << ", b = " << b << std::endl;
    ::swap( a, b );
    std::cout << "After swap: a = " << a << ", b = " << b << std::endl;
    // Min/Max
    std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
    std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;
    std::cout << std::endl;

    /*
    ** ----- Std::string ----- 
    */
    std::string c = "chaine1";
    std::string d = "chaine2";

    // Swap operation
    std::cout << "Before swap: c = " << c << ", d = " << d << std::endl;
    ::swap(c, d);
    std::cout << "After swap: c = " << c << ", d = " << d << std::endl;
    // Min/Max
    std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
    std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;
    std::cout << std::endl;

    /*
    ** ----- Bool ----- 
    */
    bool e = true;
    bool f = false;

    // Swap operation
    std::cout << "Before swap: e = " << e << ", f = " << f << std::endl;
    ::swap(e, f);
    std::cout << "After swap: e = " << e << ", f = " << f << std::endl;
    // Min/Max
    std::cout << "min( e, f ) = " << ::min( e, f ) << std::endl;
    std::cout << "max( e, f ) = " << ::max( e, f ) << std::endl;
    std::cout << std::endl;

    /*
    ** ----- Pointer ----- 
    */
    int* ptr = &a;
    int* ptr2 = &b;

    // Swap operation
    std::cout << "Before swap: ptr = " << ptr << ", ptr2 = " << ptr2 << std::endl;
    ::swap(ptr, ptr2);
    std::cout << "After swap: ptr = " << ptr << ", ptr2 = " << ptr2 << std::endl;
    // Min/Max
    std::cout << "min( ptr, ptr2 ) = " << ::min( ptr, ptr2 ) << std::endl;
    std::cout << "max( ptr, ptr2 ) = " << ::max( ptr, ptr2 ) << std::endl;

    return 0;
}