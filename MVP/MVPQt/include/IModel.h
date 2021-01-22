#pragma once
#include <iostream>
#include <ostream>
#include <thread>


#include "BackgroundWorker.h"

class IModel
{
    
public:
    explicit IModel(BackgroundWorker* pBackgroundWorker)//le background worker unique sur lequel travaille le model
        :   m_pBackgroundWorker(pBackgroundWorker)
    {
        std::cout << "model : "<<std::this_thread::get_id() <<std::endl;
    }

    virtual ~IModel() = default;

    void Print() const
    {
        m_pBackgroundWorker->Async(
          []()
          {
              std::cout << "Model : "<<std::this_thread::get_id() <<std::endl;//quand on appel print on nous dit sur quel thread on est de façon asynchrone
          }  
        );
    }

    
    //on passe une fonction avec des arguments
    template<typename... Args>
    void AsyncPost(std::function<void(Args...)>f)
    {
        m_pBackgroundWorker->Async(f);
    }

protected :
    BackgroundWorker* m_pBackgroundWorker;
    
};
