#include "ImageRenderObject.h"

#include "lib/SDL_Image_Utilities.h"

#include <SDL.h>

ImageRenderObject::ImageRenderObject(SDL_Renderer *_renderer) : GameObject(_renderer) {}
ImageRenderObject::ImageRenderObject(SDL_Renderer *_renderer, SDL_Rect *_rect) : GameObject(_renderer, _rect) {}

/**
 * Load textures by path.
 * @param path Path to a local texture.
 *
 * @deprecated DEVELOPMENT USE ONLY! Use LoadTextureRW to load textures in a final build.
 */
void ImageRenderObject::LoadTexture(const char *path)
{
    texture = SDL_Image_Utilities::LoadTexture(renderer, path);
}

/**
 * Load textures from memory buffer.
 * @param mem Pointer to a read-only buffer. (texture loaded in via header file)
 * @param size Length of a buffer in bytes.
 */
void ImageRenderObject::LoadTextureRW(const void *mem, int size)
{
    texture = SDL_Image_Utilities::LoadTextureRW(renderer, mem, size);
}

/**
 * Render image to the scene.
 */
void ImageRenderObject::Render()
{
    SDL_RenderCopy(renderer, texture, NULL, rect);
}

/**
 * Cleanup function to run after the scene is unloaded.
 */
void ImageRenderObject::Clean()
{
    SDL_DestroyTexture(texture);
}
