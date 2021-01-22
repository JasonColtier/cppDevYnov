#pragma once
#include "IModel.h"

class ConcreteModel : public IModel
{
public:
    explicit ConcreteModel(BackgroundWorker* pBackgroundWorker)
        : IModel(pBackgroundWorker)
    {
        
    }

    void Compute()
    {
        std::function<void()> f = []()
        {
            std::cout<<"concrete model thread : "<<std::this_thread::get_id()<<std::endl;
        };
        AsyncPost<>(f);
    }

    
    
};
