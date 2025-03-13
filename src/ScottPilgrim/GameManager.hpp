#pragma once

#include "../images/level.h"

#include "Handcrank/Handcrank.hpp"
#include "Handcrank/ImageRenderObject.hpp"

using namespace Handcrank;

#include "Roxzilla.hpp"
#include "ScottPilgrim.hpp"

class GameManager : public RenderObject
{
  public:
    void Start() override
    {
        game->SetTitle("Scott Pilgrim");

        game->SetScreenSize(1200, 568);

        auto image = std::make_unique<ImageRenderObject>();

        image->LoadTextureRW(game->GetRenderer(), images_level_png,
                             images_level_png_len);

        image->SetScale(4);

        game->AddChildObject(std::move(image));

        game->AddChildObject(std::make_shared<ScottPilgrim>());
        game->AddChildObject(std::make_shared<Roxzilla>());
    }

    void Update(double deltaTime) override
    {
        if (game->keyState[SDLK_ESCAPE])
        {
            game->Quit();
        }
    }
};
