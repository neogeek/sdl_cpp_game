#pragma once

#include <SDL.h>

class GameObject
{

protected:
    SDL_Renderer *renderer;

    SDL_Rect *rect;

public:
    GameObject(SDL_Renderer *_renderer);
    GameObject(SDL_Renderer *_renderer, SDL_Rect *_rect);

    void SetRect(SDL_Rect *_rect);

    virtual void Render();

    virtual void Clean();
};
