#pragma once

#include "Handcrank/Handcrank.hpp"

using namespace Handcrank;

class GameManager : public RenderObject
{

  public:
    void Start() override { game->SetTitle("Frame Rate Tester"); }

    void Update(double deltaTime) override
    {
        std::cout << "update " << deltaTime << std::endl;
    }
    void FixedUpdate(double deltaTime) override
    {
        std::cout << "fixed update " << deltaTime << std::endl;
    }
};
