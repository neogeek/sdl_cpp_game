#include "RectRenderObject.h"

#include "lib/SDL_Utilities.h"

#include <SDL.h>

RectRenderObject::RectRenderObject(SDL_Rect *_rect) : GameObject(_rect) {}

RectRenderObject::~RectRenderObject()
{
}

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
void RectRenderObject::Render(SDL_Renderer *renderer)
{
    SDL_Utilities::RenderRect(renderer, rect, color);
}

/**
 * Cleanup function to run after the scene is unloaded.
 */
void RectRenderObject::Clean()
{
}
