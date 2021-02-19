


#include <iostream>
#include <ostream>

#include "SharedPtr.h"

int main()
{
    std::cout << "begin main" <<std::endl;

    SharedPtr<int> p(3);
    std::cout << p.GetCount() <<std::endl;

    auto pCopy = p;
    std::cout << p.GetCount() <<std::endl;

    {//scope manuel 
        SharedPtr<int> q;
        if(!q)
        {
            std::cout << "null"<<std::endl;
        }

        q = p;
        if(q)
        {
            std::cout << "plus null"<<std::endl;
        }

        std::cout << "q value : "<< *q <<std::endl;
        std::cout << p.GetCount() <<std::endl;

    }

    std::cout << p.GetCount() <<std::endl;

    
    return 0;
}
