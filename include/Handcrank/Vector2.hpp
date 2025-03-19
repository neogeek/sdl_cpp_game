#pragma once

#include <algorithm>

#include <SDL.h>

namespace Handcrank
{

struct Vector2
{
    float x;
    float y;

    Vector2() : x(0), y(0) {}
    Vector2(const float x, const float y) : x(x), y(y) {}
    explicit Vector2(const SDL_FPoint point) : x(point.x), y(point.y) {}
    explicit Vector2(const SDL_FRect rect) : x(rect.x), y(rect.y) {}

    auto operator+(const Vector2 &other) const -> Vector2
    {
        return {x + other.x, y + other.y};
    }

    auto operator-(const Vector2 &other) const -> Vector2
    {
        return {x - other.x, y - other.y};
    }

    auto operator*(const float number) const -> Vector2
    {
        return {x * number, y * number};
    }

    auto operator/(const float number) const -> Vector2
    {
        if (number == 0)
        {
            throw std::invalid_argument("Can't divide by zero.\n");
        }

        return {x / number, y / number};
    }

    static auto Lerp(const Vector2 &start, const Vector2 &destination,
                     const float t) -> Vector2
    {
        return LerpUnclamped(start, destination, std::clamp<float>(t, 0, 1));
    }

    static auto LerpUnclamped(const Vector2 &start, const Vector2 &destination,
                              const float t) -> Vector2
    {
        auto newPosition = Vector2(start);

        newPosition.x += (destination.x - start.x) * t;
        newPosition.y += (destination.y - start.y) * t;

        return newPosition;
    }

    [[nodiscard]] auto ToFPoint() const -> SDL_FPoint { return {x, y}; }

    [[nodiscard]] auto ToFRect() const -> SDL_FRect { return {x, y}; }
};

} // namespace Handcrank
