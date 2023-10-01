#include "RectRenderObject.h"

#include "lib/SDL_Utilities.h"

#include <SDL.h>

RectRenderObject::RectRenderObject(SDL_Renderer *_renderer) : GameObject(_renderer) {}
RectRenderObject::RectRenderObject(SDL_Renderer *_renderer, SDL_Rect *_rect) : GameObject(_renderer, _rect) {}

void RectRenderObject::SetColor(SDL_Color _color)
{
    color = _color;
}

void RectRenderObject::Render()
{
    SDL_Utilities::RenderRect(renderer, rect, color);
}

void RectRenderObject::Clean()
{
}
