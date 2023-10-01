#pragma once

#include <SDL.h>

#include <GameObject.h>

class RenderObject : public GameObject
{

private:
    SDL_Color color;

public:
    RenderObject(SDL_Renderer *_renderer);
    RenderObject(SDL_Renderer *_renderer, SDL_Rect *_rect);

    void SetColor(SDL_Color _color);

    void Render() override;

    void Clean() override;
};
