#include "ImageRenderObject.h"

#include "lib/SDL_Image_Utilities.h"

#include <SDL.h>

ImageRenderObject::ImageRenderObject(SDL_Renderer *_renderer) : RenderObject(_renderer) {}
ImageRenderObject::ImageRenderObject(SDL_Renderer *_renderer, SDL_Rect *_rect) : RenderObject(_renderer, _rect) {}

void ImageRenderObject::Render()
{
    SDL_RenderCopy(renderer, texture, NULL, rect);
}

void ImageRenderObject::LoadTexture(const char *path)
{
    texture = SDL_Image_Utilities::LoadTexture(renderer, path);
}

void ImageRenderObject::Clean()
{
    SDL_DestroyTexture(texture);
}
