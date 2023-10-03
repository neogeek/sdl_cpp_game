#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "lib/SDL_Utilities.h"
#include "lib/SDL_TTF_Utilities.h"

#include <GameObject.h>

class TextRenderObject : public GameObject
{

private:
    TTF_Font *font;

    SDL_Color color{255, 255, 255, 255};

    const char *text;

public:
    explicit TextRenderObject(SDL_Rect *_rect) : GameObject(_rect) {}

    ~TextRenderObject()
    {
    }

    /**
     * Set text font.
     * @param font Font value to set.
     */
    inline void SetFont(TTF_Font *_font)
    {
        font = _font;
    }

    /**
     * Set text color.
     * @param color Color value to set.
     */
    inline void SetColor(SDL_Color _color)
    {
        color = _color;
    }

    /**
     * Set text content.
     * @param text Text value to set.
     */
    inline void SetText(const char *_text)
    {
        text = _text;
    }

    /**
     * Render text to the scene.
     */
    inline void Render(SDL_Renderer *renderer)
    {
        SDL_TTF_Utilities::RenderText(renderer, font, color, *rect, text);
    }

    /**
     * Cleanup function to run after the scene is unloaded.
     */
    inline void Clean()
    {
    }
};
