#pragma once
#include <iostream>
#include <ostream>

class IView
{
    
public:
    explicit IView()
    {
        std::cout<<"create view"<<std::endl;
    }

    virtual  ~IView() = default;//interface = destructeur virtuel
    
};
