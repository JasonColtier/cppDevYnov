#include "ConcreteView.h"
#include "QPushButton"

ConcreteView::ConcreteView(QWidget* pParent) : IView(pParent)
{
    Init();
    Handle();
}

void ConcreteView::Init()
{
    m_pButton = std::make_unique<QPushButton>("test",this);
}

void ConcreteView::Handle()
{
    
}
