#pragma once
#include <iostream>
#include <ostream>
#include <QWidget>
#include <thread>

class IView : public QWidget
{
    
public:
    explicit IView(QWidget* pParent = nullptr)
        :QWidget(pParent)
    {
        std::cout<<"create view "<<std::this_thread::get_id()<<std::endl;
    }

    virtual  ~IView() = default;//interface = destructeur virtuel
    
};
