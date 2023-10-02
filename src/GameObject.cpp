#include "GameObject.h"

#include "lib/SDL_Utilities.h"

#include <SDL.h>

GameObject::GameObject() {}
GameObject::GameObject(SDL_Renderer *_renderer) : renderer(_renderer) {}
GameObject::GameObject(SDL_Renderer *_renderer, SDL_Rect *_rect) : renderer(_renderer), rect(_rect) {}

void GameObject::SetRect(SDL_Rect *_rect)
{
    rect = _rect;
}

void GameObject::Render()
{
}

void GameObject::Clean()
{
}
