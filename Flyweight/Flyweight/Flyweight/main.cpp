#include <iostream>
#include <iterator>
#include <ostream>
#include <vector>
#include "TreeModel.h"
#include "Tree.h"


int main()
{
    auto pTreeModel = std::make_shared<TreeModel>(); //création du tree model  (=1)

    std::cout <<pTreeModel.use_count()<<std::endl;//combien d'objet pointent sur mon shared pointer ?

    std::vector<std::unique_ptr<Tree>> trees(10); //on crée un array avec 10 places


    
    //on remplie le tableau
    for (auto& pTree : trees)
    {
        pTree = std::make_unique<Tree>(pTreeModel);
        pTree->SetHeight(std::rand() * 10);
        pTree->SetRadius(std::rand());//c'est pas comme ça qu'on fait un bon random

        std::cout <<"pointer : "<<pTreeModel.use_count()<<std::endl;//combien d'objet pointent sur mon shared pointer ?

        std::cout << "reference : " << pTree->GetTreeModel() << std::endl;
        //on vérifie que tous les arbres pointent sur le même modèle
    }

    //on vérifie qu'on a des valeurs différentes et on affiche nos arbres
    for (auto& pTree : trees)
    {
        std::cout << "Height : " << pTree->GetHeight() << std::endl;
        std::cout << "Radius : " << pTree->GetRadius() << std::endl;
    }

    //création d'un problème

    return 0;
}
