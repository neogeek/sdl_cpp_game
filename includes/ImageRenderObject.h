#pragma once

#include <memory>

#include <SDL.h>

#include "sdl/SDL_Image_Utilities.h"
#include "sdl/SDL_Texture_Deleter.h"

#include "GameObject.h"

class ImageRenderObject : public GameObject
{
  private:
    std::unique_ptr<SDL_Texture, SDL_Texture_Deleter> texture;

  public:
    explicit ImageRenderObject() : GameObject() {}
    explicit ImageRenderObject(SDL_Rect *_rect) : GameObject(_rect) {}

    ~ImageRenderObject() { SDL_DestroyTexture(texture.get()); }

    /**
     * Load textures by path.
     * @param path Path to a local texture.
     *
     * @deprecated DEVELOPMENT USE ONLY! Use LoadTextureRW to load textures in a
     * final build.
     */
    void LoadTexture(SDL_Renderer *renderer, const char *path)
    {
        texture = SDL_Image_Utilities::LoadTexture(renderer, path);
    }

    /**
     * Load textures from memory buffer.
     * @param mem Pointer to a read-only buffer. (texture loaded in via header
     * file)
     * @param size Length of a buffer in bytes.
     */
    void LoadTextureRW(SDL_Renderer *renderer, const void *mem, int size)
    {
        texture =
            std::move(SDL_Image_Utilities::LoadTextureRW(renderer, mem, size));
    }

    /**
     * Render image to the scene.
     */
    void Render(SDL_Renderer *renderer) override
    {
        SDL_RenderCopy(renderer, texture.get(), nullptr, rect);
    }

    /**
     * Cleanup function to run after the scene is unloaded.
     */
    void Clean() override {}
};
