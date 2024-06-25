#include <iostream>
#include "Base.hpp"

int main()
{
    srand(time(0));

    Base source;

    // Test pointers
    Base* base_ptr1 = source.generate();
    Base* base_ptr2 = source.generate();
    Base* base_ptr3 = source.generate();
    source.identify(base_ptr1); 
    source.identify(base_ptr2);
    source.identify(base_ptr3);

    // Test reference
    Base* base_ref1 = source.generate();
    Base* base_ref2 = source.generate();
    Base* base_ref3 = source.generate();
    source.identify(*base_ref1); 
    source.identify(*base_ref2);
    source.identify(*base_ref3);

    // Delete tests
    delete base_ptr1;
    delete base_ptr2;
    delete base_ptr3;
    delete base_ref1;
    delete base_ref2;
    delete base_ref3;
    return 0;
}
