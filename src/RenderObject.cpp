#include "RenderObject.h"

#include "lib/SDL_Utilities.h"

#include <SDL.h>

RenderObject::RenderObject(SDL_Renderer *_renderer) : renderer(_renderer) {}
RenderObject::RenderObject(SDL_Renderer *_renderer, SDL_Rect _rect) : renderer(_renderer), rect(_rect) {}

void RenderObject::Render()
{
    SDL_Utilities::RenderRect(renderer, rect, color);
}
