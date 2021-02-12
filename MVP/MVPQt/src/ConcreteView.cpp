#include "ConcreteView.h"

ConcreteView::ConcreteView(QWidget* pParent /* = nullptr */)
	: IView(pParent)
{
	Init();
	Handle();
}

void ConcreteView::Init()
{
	m_pButton = std::make_unique<QPushButton>("Test", this);
}

void ConcreteView::Handle()
{
	connect(m_pButton.get(), &QPushButton::clicked, this, &ConcreteView::TestView);
}

void ConcreteView::TestView()
{
	std::cout << "Post view: " << std::this_thread::get_id() << std::endl;
	TRIG_EVENT(buttonPushed)
}
