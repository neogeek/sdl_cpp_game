#include "RenderObject.h"

#include "lib/SDL_Utilities.h"

#include <SDL.h>

RenderObject::RenderObject(SDL_Renderer *_renderer) : renderer(_renderer) {}
RenderObject::RenderObject(SDL_Renderer *_renderer, SDL_Rect *_rect) : renderer(_renderer), rect(_rect) {}

void RenderObject::Render()
{
    SDL_Utilities::RenderRect(renderer, rect, color);
}

void RenderObject::SetRect(SDL_Rect *_rect)
{
    rect = _rect;
}

void RenderObject::SetColor(SDL_Color _color)
{
    color = _color;
}
