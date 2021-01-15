#pragma once
#include <cwchar>
#include <memory>
#include <iostream>
#include <ostream>



#include "TreeModel.h"

class Color
{};

class Tree
{

public:
    explicit Tree(std::shared_ptr<TreeModel> m_pTreeModel) ://(=2)
    //m_pTreeModel(m_pTreeModel),//objet temporaire qui fait aussi une référence (=3)
    m_pTreeModel(std::move(m_pTreeModel)),//en passant par std::move on enlève cet objet temporaire
    m_height(10),
    m_radius(1) 
    {
        std::cout <<m_pTreeModel.use_count()<<std::endl;//combien d'objet pointent sur mon shared pointer ?
    }

    ~Tree() = default;

    void SetHeight(const int& height)
    {
        m_height = height;
    }

    void SetRadius(const int& radius)// const pour s'assurer que c'est pas modifié par l'appelant
    {
        m_radius = radius;
    }

    int GetHeight() const//const pour s'assurer qu'il n'y a pas de modif par la fonction et qu'elle est optimisée par le compilateur
    {
        return m_height;
    }

    int GetRadius() const
    {
        return  m_radius;
    }

    TreeModel* GetTreeModel() const
    {
        return m_pTreeModel.get();
    }

private:
    int m_height;
    int m_radius;
    std::shared_ptr<TreeModel> m_pTreeModel;//problème ce shared pointeur est duppliqué
    Color m_truncColor;
    Color m_foliageColor;
};
