#include "ConcretePresenter.h"

ConcretePresenter::ConcretePresenter()
	: IPresenter()
{
	SYNC_OBS(m_value)
	ConfigureDispatcherFromView();
}

void ConcretePresenter::ConfigureDispatcherFromModel()
{
}

void ConcretePresenter::ConfigureDispatcherFromView()
{
	DISPATCH_FROM_VIEW(buttonPushed, TestModel, ConcreteModel);
}
