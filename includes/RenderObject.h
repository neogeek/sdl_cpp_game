#pragma once

#include <SDL.h>

class RenderObject
{

private:
    SDL_Renderer *renderer;

    SDL_Rect rect;

public:
    RenderObject(SDL_Renderer *_renderer);
    RenderObject(SDL_Renderer *_renderer, SDL_Rect _rect);

    void Render();
};
