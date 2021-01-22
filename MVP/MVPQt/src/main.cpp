
#include "ConcretePresenter.h"
#include <iostream>
#include <QtWidgets/QApplication>

int main(int argc,char* argv[])
{
    // const auto pPresenter = std::make_unique<ConcretePresenter>();
    // auto pModel = dynamic_cast<ConcreteModel*>(pPresenter->GetModel());
    // auto pView = dynamic_cast<ConcreteView*>(pPresenter->GetView());
    //
    // while (true)
    // {
    //     std::cout<<"ui : "<<std::this_thread::get_id()<<std::endl;
    //
    //
    //     pModel->Compute();
    //     pView->Display();
    // }

    QApplication app(argc,argv);

    auto pPresenterWidget = std::make_unique<ConcretePresenter>();
    pPresenterWidget->GetView()->show();

    return app.exec();
    





    return 0;
}
