#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

/*
** --------------------------- Virtual Destructor ------------------------------
*/
Base::~Base() {}


/*
** ---------------------------- Member Functions -------------------------------
*/
Base* Base::generate(void) const
{
    int random_nb = rand() % 3;

    std::cout << "random_nb: " << random_nb << std::endl;
    switch (random_nb)
    {
        case 0:
            return new A();
            break;
        case 1:
            return new B();
            break;
        case 2:
            return new C();
            break;
        default:
            return NULL;
    }
}

void Base::identify(Base* p) const
{
    if (dynamic_cast<A*>(p))
        std::cout << "This class is an A\n";
    else if (dynamic_cast<B*>(p))
        std::cout << "This class is an B\n";
    else if (dynamic_cast<C*>(p))
        std::cout << "This class is an C\n";
    else
        std::cout << "Type is not know, sorry\n";
}

void Base::identify(Base& p) const
{
    try
    {
        if (dynamic_cast<A*>(&p))
        {
            std::cout << "This class is an A\n";
            return ;
        }
    }
    catch(const std::exception* e) { }
    
    try
    {
        if (dynamic_cast<B*>(&p))
        {
            std::cout << "This class is an B\n";
            return ;
        }
    }
    catch(const std::exception* e) { }

    try
    {
        if (dynamic_cast<C*>(&p))
        {
            std::cout << "This class is an C\n";
            return ;
        }
    }
    catch(const std::exception* e) { }
    
    std::cout << "Type is not know, sorry\n";
}