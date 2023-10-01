#pragma once

#include <SDL.h>

class RenderObject
{

protected:
    SDL_Renderer *renderer;

    SDL_Rect *rect;

    SDL_Color color;

public:
    RenderObject(SDL_Renderer *_renderer);
    RenderObject(SDL_Renderer *_renderer, SDL_Rect *_rect);

    void Render();

    void SetRect(SDL_Rect *_rect);
    void SetColor(SDL_Color _color);

    void Clean();
};
