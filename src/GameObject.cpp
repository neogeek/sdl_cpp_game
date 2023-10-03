#include "GameObject.h"

#include "lib/SDL_Utilities.h"

#include <SDL.h>

GameObject::GameObject(SDL_Rect *_rect) : rect(_rect) {}

GameObject::~GameObject() {}

/**
 * Set rect position and size to the GameObject.
 * @param rect A rectangle, with the origin at the upper left (integer).
 */
void GameObject::SetRect(SDL_Rect *_rect)
{
    rect = _rect;
}

/**
 * Render GameObject to the scene.
 */
void GameObject::Render(SDL_Renderer *_renderer)
{
}

/**
 * Cleanup function to run after the scene is unloaded.
 */
void GameObject::Clean()
{
}
