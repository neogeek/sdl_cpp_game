#pragma once

#include <SDL.h>

struct SDL_Texture_Deleter
{
    void operator()(SDL_Texture *texture) const { SDL_DestroyTexture(texture); }
};
