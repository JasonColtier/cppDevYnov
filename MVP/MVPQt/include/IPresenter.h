#pragma once

#include "IView.h"
#include "IModel.h"
#include "Threading.h"

template<typename Model, typename View>
class IPresenter : public  Threading<IModel,IView>
{
public:
    //je ne veux pas avoir à y passer des paramètres, c'est lui qui les instencie
    IPresenter()
        : m_pModel(std::make_shared<Model>(m_pBackgroundWorker.get())),
        m_pView(std::make_shared<View>())
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
    std::shared_ptr<IModel> m_pModel;
    std::shared_ptr<IView> m_pView;
    
};

