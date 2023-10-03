#pragma once

#include <SDL.h>

#include "lib/SDL_Image_Utilities.h"

#include <GameObject.h>

class ImageRenderObject : public GameObject
{

private:
    SDL_Texture *texture;

public:
    explicit ImageRenderObject(SDL_Rect *_rect) : GameObject(_rect) {}

    ~ImageRenderObject()
    {
        SDL_DestroyTexture(texture);
    }

    /**
     * Load textures by path.
     * @param path Path to a local texture.
     *
     * @deprecated DEVELOPMENT USE ONLY! Use LoadTextureRW to load textures in a final build.
     */
    inline void LoadTexture(SDL_Renderer *renderer, const char *path)
    {
        texture = SDL_Image_Utilities::LoadTexture(renderer, path);
    }

    /**
     * Load textures from memory buffer.
     * @param mem Pointer to a read-only buffer. (texture loaded in via header file)
     * @param size Length of a buffer in bytes.
     */
    inline void LoadTextureRW(SDL_Renderer *renderer, const void *mem, int size)
    {
        texture = SDL_Image_Utilities::LoadTextureRW(renderer, mem, size);
    }

    /**
     * Render image to the scene.
     */
    inline void Render(SDL_Renderer *renderer)
    {
        SDL_RenderCopy(renderer, texture, NULL, rect);
    }

    /**
     * Cleanup function to run after the scene is unloaded.
     */
    inline void Clean()
    {
    }
};
