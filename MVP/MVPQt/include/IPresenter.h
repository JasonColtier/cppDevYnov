#ifndef IPRESENTER_H
#define IPRESENTER_H

#include "Threading.h"
#include "IView.h"
#include "IModel.h"
#include "Dispatcher.h"
#include <memory>

template<typename Model, typename View>
class IPresenter : public Threading<Model, View>
{
public:
    //je ne veux pas avoir à y passer des paramètres, c'est lui qui les instencie
	IPresenter()
		: m_pModel(std::make_shared<Model>(m_pBackgroundWorker.get()))
		, m_pView(std::make_shared<View>())
	{
	}

	IModel* GetModel() const
	{
		return m_pModel.get();
	}

	IView* GetView() const
	{
		return m_pView.get();
	}

	virtual ~IPresenter() = default;

protected:
	virtual void ConfigureDispatcherFromView(){}
	virtual void ConfigureDispatcherFromModel(){}
	
	std::shared_ptr<Model> m_pModel;
	std::shared_ptr<View> m_pView;
};

#endif // IPRESENTER_H