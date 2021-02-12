#include "ConcreteModel.h"

ConcreteModel::ConcreteModel(BackgroundWorker* pBackgroundWorker): IModel(pBackgroundWorker)
{
}


DEFINE_VIEW_FUNCTION_LINKABLE(ConcreteModel, TestModel)
{
	const std::function<void()> f = [this]()
	{
		std::cout << "Test in the model" << std::endl;
		std::cout << "Post: " << std::this_thread::get_id() << std::endl;
		m_value_obs = 4;
	};

	AsyncPost<>(f);
}
