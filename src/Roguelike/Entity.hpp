#pragma once

#include "Handcrank/Handcrank.hpp"
#include "Handcrank/RectRenderObject.hpp"

using namespace Handcrank;

class Entity : public RectRenderObject
{

  protected:
    int width = 20;
    int height = 20;

    int minX = 0;
    int maxX = 0;

    int minY = 0;
    int maxY = 0;

  public:
    void Start() override
    {
        auto transformedRect = GetTransformedRect();

        SetRect(0, 0, width, height);

        maxX = game->GetWidth() - transformedRect.w;
        maxY = game->GetHeight() - transformedRect.h;

        SetFillColor(255, 255, 255, 255);
    }
};
