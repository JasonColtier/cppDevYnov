



#include <iostream>
#include <ostream>

#include "TypeTest.h"

struct A
{
    
};

struct B
{
    
};

int main()
{
    std::cout << "begin main" << std::endl;

    const char* lhs = "tata";
    const char* rhs = "tat";

    std::cout << std::boolalpha << StringCompare(lhs,rhs) << std::endl;

    if(IsSame<A,B>::value)
        std::cout << "problem ! "<< std::endl;
    else
    {
        std::cout << "it works approximately"<<std::endl;
    }

    if(IsSame<A,A>::value)
        std::cout << "it works ! "<< std::endl;
    
    return 0;
}
