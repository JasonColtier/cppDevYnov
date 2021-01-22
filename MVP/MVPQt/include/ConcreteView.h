#pragma once

#include "IView.h"
#include <QWidget>

class QPushButton;

class ConcreteView : public IView
{
public:
    explicit ConcreteView( QWidget* pParent = nullptr);
    ~ConcreteView() = default;

    void Display()
    {
        std::cout<<"concrete view thread : "<<std::this_thread::get_id()<<std::endl;
    }

private:
    void Init();
    void Handle();

    std::unique_ptr<QPushButton> m_pButton;
};
