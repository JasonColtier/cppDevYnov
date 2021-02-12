#ifndef CONCRETEVIEW_H
#define CONCRETEVIEW_H

#include "IView.h"

#include <thread>
#include <QPushButton>


class ConcreteView : public IView
{
public:
	explicit ConcreteView(QWidget* pParent = nullptr);
	~ConcreteView() = default;

	DEFINE_EVENT(buttonPushed)
	DECLARE_OBS(m_value, int)

	void Display()
	{
		std::cout << "View displayed on this thread: " << std::this_thread::get_id() << std::endl;
	}

private:
	void Init();
	void Handle();
	void TestView();

	std::unique_ptr<QPushButton> m_pButton;
};


#endif // CONCRETEVIEW_H
