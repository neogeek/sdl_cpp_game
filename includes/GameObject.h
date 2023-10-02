#pragma once

#include <SDL.h>

class GameObject
{

protected:
    SDL_Rect *rect;

public:
    GameObject(SDL_Rect *_rect);

    void SetRect(SDL_Rect *_rect);

    virtual void Render(SDL_Renderer *renderer);

    virtual void Clean();
};
