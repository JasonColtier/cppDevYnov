#pragma once
#include <iostream>
#include <ostream>
#include <thread>

class IView
{
    
public:
    explicit IView()
    {
        std::cout<<"create view "<<std::this_thread::get_id()<<std::endl;
    }

    virtual  ~IView() = default;//interface = destructeur virtuel
    
};
