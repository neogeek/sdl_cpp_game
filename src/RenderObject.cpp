#include "RenderObject.h"

#include <SDL.h>

RenderObject::RenderObject(SDL_Renderer *_renderer, SDL_Rect _rect) : renderer(_renderer), rect(_rect) {}

void RenderObject::Render()
{
    SDL_Color color = {255, 255, 255, 255};

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_RenderFillRect(renderer, &rect);
}
