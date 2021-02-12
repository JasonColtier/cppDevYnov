#ifndef CONCRETEPRESENTER_H
#define CONCRETEPRESENTER_H

#include "IPresenter.h"
#include "ConcreteModel.h"
#include "ConcreteView.h"

class ConcretePresenter : public IPresenter<ConcreteModel, ConcreteView>
{
public:
    //pas plus compliqué que ça !
    //il pourrai tmm être fait à la volée dans le main
	ConcretePresenter();
	~ConcretePresenter() = default;

protected:
	void ConfigureDispatcherFromModel() override;
	void ConfigureDispatcherFromView() override;
};

#endif // CONCRETEPRESENTER_H
