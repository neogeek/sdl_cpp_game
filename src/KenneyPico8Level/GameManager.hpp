#pragma once

#include "Handcrank/Handcrank.hpp"

using namespace Handcrank;

class GameManager : public RenderObject
{

  public:
    void Start() override { game->SetTitle("Kenney Pico 8 Level"); }
};
