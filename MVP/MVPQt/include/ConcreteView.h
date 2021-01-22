#pragma once

#include "IView.h"

class ConcreteView : public IView
{
public:
    ConcreteView() = default;
    ~ConcreteView() = default;

    void Display()
    {
        std::cout<<"concrete view thread : "<<std::this_thread::get_id()<<std::endl;
    }
};
