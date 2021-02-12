#pragma once
#include <iostream>
#include <ostream>
#include <QWidget>
#include <thread>
#include "Dispatcher.h"

class IView : public QWidget
{
    Q_OBJECT

public:
    explicit IView(QWidget* pParent = nullptr)
        :QWidget(pParent)
    {
        std::cout<<"create view "<<std::this_thread::get_id()<<std::endl;
    }

    virtual  ~IView() = default;//interface = destructeur virtuel

    
};
