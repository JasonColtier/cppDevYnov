#pragma once
#include "ConcreteModel.h"
#include "ConcreteView.h"
#include "IPresenter.h"


class ConcretePresenter : public IPresenter<ConcreteModel,ConcreteView>
{
    
public:
    //pas plus compliqué que ça !
    //il pourrai tmm être fait à la volée dans le main
    
};
