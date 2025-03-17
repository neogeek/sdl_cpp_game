// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include <SDL.h>

#include "Handcrank.hpp"
#include "Handcrank/ImageRenderObject.hpp"
#include "Handcrank/Vector2.hpp"

namespace Handcrank
{

class SpriteRenderObject : public ImageRenderObject
{

  private:
    std::shared_ptr<std::vector<SDL_Rect>> spriteFrames =
        std::make_shared<std::vector<SDL_Rect>>();

    int frame = 0;

    double frameSpeed = 0.1;

    bool isPlaying = false;

    double nextTick;

  public:
    explicit SpriteRenderObject() {}
    explicit SpriteRenderObject(const SDL_FRect _rect) { SetRect(_rect); }

    ~SpriteRenderObject() = default;

    void Play() { isPlaying = true; }
    void Pause() { isPlaying = false; }
    void Stop()
    {
        frame = 0;
        isPlaying = false;
    }

    void SetFrameSpeed(const double _frameSpeed) { frameSpeed = _frameSpeed; }

    void SetFrames(std::shared_ptr<std::vector<SDL_Rect>> _spriteFrames)
    {
        spriteFrames.reset();

        spriteFrames = _spriteFrames;
    }

    void CalculateFrames(float width, float height, int columns, int rows,
                         Vector2 padding, Vector2 offset)
    {
        spriteFrames->clear();

        auto availableWidth = width - (padding.x * (columns - 1));
        auto availableHeight = height - (padding.y * (rows - 1));

        auto cellWidth = availableWidth / columns;
        auto cellHeight = availableHeight / rows;

        for (auto x = 0; x < columns; x++)
        {
            for (auto y = 0; y < rows; y++)
            {
                SDL_Rect rect;

                rect.x =
                    static_cast<int>((offset.x + x) * (cellWidth + padding.x));
                rect.y =
                    static_cast<int>((offset.y + y) * (cellHeight + padding.y));
                rect.w = static_cast<int>(cellWidth);
                rect.h = static_cast<int>(cellHeight);

                spriteFrames->push_back(rect);
            }
        }
    }

    void InternalUpdate(const double deltaTime) override
    {
        ImageRenderObject::InternalUpdate(deltaTime);

        if (!isPlaying)
        {
            return;
        }

        auto spriteFramesSize = spriteFrames.get()->size();

        nextTick += deltaTime;

        if (nextTick < frameSpeed)
        {
            return;
        }

        frame += 1;

        if (frame == spriteFramesSize)
        {
            frame = 0;
        }

        nextTick = 0;
    }

    void Render(std::shared_ptr<SDL_Renderer> renderer) override
    {
        if (!CanRender())
        {
            return;
        }

        auto spriteFramesSize = spriteFrames.get()->size();

        if (spriteFramesSize <= frame)
        {
            return;
        }

        auto srcRect = spriteFrames.get()->at(frame);

        SetSrcRect(srcRect);

        rect->w = srcRect.w;
        rect->h = srcRect.h;

        ImageRenderObject::Render(renderer);
    }
};

} // namespace Handcrank
