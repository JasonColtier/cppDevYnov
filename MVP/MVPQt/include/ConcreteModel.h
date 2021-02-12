#ifndef CONCRETEMODEL_H
#define CONCRETEMODEL_H

#include "IModel.h"
#include <thread>

class ConcreteModel : public IModel
{
public:
	explicit ConcreteModel(BackgroundWorker* pBackgroundWorker);
	~ConcreteModel() = default;


	DECLARE_VIEW_FUNCTION_LINKABLE(TestModel)
	DECLARE_OBS(m_value, int)
};

#endif // CONCRETEMODEL_H
