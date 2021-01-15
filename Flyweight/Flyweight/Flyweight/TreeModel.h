#pragma once

//declaration pour aller vite et tester
class Mesh
{};

class TruncTexture
{};

class FoliageTexture
{};

class TreeModel
{
public:
    TreeModel() = default;
    ~TreeModel() = default;


    Mesh GetMesh() const//const parce que c'est pas modifié of course
    {
        return m_mesh;
    }

    TruncTexture GetTruncTexture() const
    {
        return m_truncTexture;
    }

    FoliageTexture GetFoiliageTexture() const
    {
        return m_foliageTexture;
    }

private:
    Mesh m_mesh;
    TruncTexture m_truncTexture;
    FoliageTexture m_foliageTexture;
};
