#include "RenderObject.h"

#include "lib/SDL_Utilities.h"

#include <SDL.h>

RenderObject::RenderObject(SDL_Renderer *_renderer) : GameObject(_renderer) {}
RenderObject::RenderObject(SDL_Renderer *_renderer, SDL_Rect *_rect) : GameObject(_renderer, _rect) {}

void RenderObject::SetColor(SDL_Color _color)
{
    color = _color;
}

void RenderObject::Render()
{
    SDL_Utilities::RenderRect(renderer, rect, color);
}

void RenderObject::Clean()
{
}
