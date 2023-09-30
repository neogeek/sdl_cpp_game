#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include <SDL.h>

class RenderObject
{

private:
    SDL_Renderer *renderer;

    SDL_Rect rect;

public:
    RenderObject(SDL_Renderer *_renderer, SDL_Rect _rect);

    void Render();
};

#endif
