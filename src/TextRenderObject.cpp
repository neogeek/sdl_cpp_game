#include "TextRenderObject.h"

#include "lib/SDL_Utilities.h"
#include "lib/SDL_TTF_Utilities.h"

#include <SDL.h>

TextRenderObject::TextRenderObject(SDL_Rect *_rect) : GameObject(_rect) {}

TextRenderObject::~TextRenderObject()
{
}

/**
 * Set text font.
 * @param font Font value to set.
 */
void TextRenderObject::SetFont(TTF_Font *_font)
{
    font = _font;
}

/**
 * Set text color.
 * @param color Color value to set.
 */
void TextRenderObject::SetColor(SDL_Color _color)
{
    color = _color;
}

/**
 * Set text content.
 * @param text Text value to set.
 */
void TextRenderObject::SetText(const char *_text)
{
    text = _text;
}

/**
 * Render text to the scene.
 */
void TextRenderObject::Render(SDL_Renderer *renderer)
{
    SDL_TTF_Utilities::RenderText(renderer, font, color, *rect, text);
}

/**
 * Cleanup function to run after the scene is unloaded.
 */
void TextRenderObject::Clean()
{
}
