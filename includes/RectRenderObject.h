#pragma once

#include <SDL.h>

#include <GameObject.h>

class RectRenderObject : public GameObject
{

private:
    SDL_Color color;

public:
    RectRenderObject(SDL_Rect *_rect);

    void SetColor(SDL_Color _color);

    void Render(SDL_Renderer *renderer) override;

    void Clean() override;
};
