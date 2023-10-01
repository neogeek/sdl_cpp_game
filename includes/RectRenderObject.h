#pragma once

#include <SDL.h>

#include <GameObject.h>

class RectRenderObject : public GameObject
{

private:
    SDL_Color color;

public:
    RectRenderObject(SDL_Renderer *_renderer);
    RectRenderObject(SDL_Renderer *_renderer, SDL_Rect *_rect);

    void SetColor(SDL_Color _color);

    void Render() override;

    void Clean() override;
};
