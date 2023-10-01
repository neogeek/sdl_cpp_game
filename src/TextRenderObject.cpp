#include "TextRenderObject.h"

#include "lib/SDL_Utilities.h"
#include "lib/SDL_TTF_Utilities.h"

#include <SDL.h>

TextRenderObject::TextRenderObject(SDL_Renderer *_renderer) : GameObject(_renderer) {}
TextRenderObject::TextRenderObject(SDL_Renderer *_renderer, SDL_Rect *_rect) : GameObject(_renderer, _rect) {}

void TextRenderObject::SetFont(TTF_Font *_font)
{
    font = _font;
}

void TextRenderObject::SetColor(SDL_Color _color)
{
    color = _color;
}

void TextRenderObject::SetText(const char *_text)
{
    text = _text;
}

void TextRenderObject::Render()
{
    SDL_TTF_Utilities::RenderText(renderer, font, color, *rect, text);
}

void TextRenderObject::Clean()
{
}
