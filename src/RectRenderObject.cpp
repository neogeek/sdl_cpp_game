#include "RectRenderObject.h"

#include "lib/SDL_Utilities.h"

#include <SDL.h>

RectRenderObject::RectRenderObject(SDL_Renderer *_renderer) : GameObject(_renderer) {}
RectRenderObject::RectRenderObject(SDL_Renderer *_renderer, SDL_Rect *_rect) : GameObject(_renderer, _rect) {}

/**
 * Set rect color.
 * @param color Color value to set.
 */
void RectRenderObject::SetColor(SDL_Color _color)
{
    color = _color;
}

/**
 * Render rect to the scene.
 */
void RectRenderObject::Render()
{
    SDL_Utilities::RenderRect(renderer, rect, color);
}

/**
 * Cleanup function to run after the scene is unloaded.
 */
void RectRenderObject::Clean()
{
}
