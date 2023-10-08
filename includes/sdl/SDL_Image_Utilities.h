#pragma once

#include <memory>

#include <SDL.h>
#include <SDL_image.h>

#include "SDL_Texture_Deleter.h"

class SDL_Image_Utilities
{
  public:
    /**
     * Load texture from a path.
     *
     * @param renderer A structure representing rendering state.
     * @param path File path to texture file.
     */
    [[nodiscard]] static std::unique_ptr<SDL_Texture, SDL_Texture_Deleter>
    LoadTexture(SDL_Renderer *renderer, const char *path)
    {
        std::unique_ptr<SDL_Surface> surface(IMG_Load(path));

        if (!surface)
        {
            return nullptr;
        }

        std::unique_ptr<SDL_Texture, SDL_Texture_Deleter> texture(
            SDL_CreateTextureFromSurface(renderer, surface.get()));

        SDL_FreeSurface(surface.get());

        if (!texture)
        {
            return nullptr;
        }

        return texture;
    }

    /**
     * Load texture from a read-only buffer.
     *
     * @param renderer A structure representing rendering state.
     * @param mem A pointer to a read-only buffer.
     * @param size The buffer size, in bytes.
     */
    [[nodiscard]] static std::unique_ptr<SDL_Texture, SDL_Texture_Deleter>
    LoadTextureRW(SDL_Renderer *renderer, const void *mem, int size)
    {
        std::unique_ptr<SDL_RWops> rw(SDL_RWFromConstMem(mem, size));

        std::unique_ptr<SDL_Surface> surface(IMG_Load_RW(rw.get(), 1));

        if (!surface)
        {
            return nullptr;
        }

        std::unique_ptr<SDL_Texture, SDL_Texture_Deleter> texture(
            SDL_CreateTextureFromSurface(renderer, surface.get()));

        SDL_FreeSurface(surface.get());

        if (!texture)
        {
            return nullptr;
        }

        return texture;
    }
};
