#pragma once

#include <algorithm>

#include <SDL.h>

struct Vector3
{
    float x;
    float y;
    float z;

    Vector3() : x(0), y(0), z(0) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    explicit Vector3(const SDL_FPoint point) : x(point.x), y(point.y) {}
    explicit Vector3(const SDL_FRect rect) : x(rect.x), y(rect.y) {}

    Vector3 operator+(const Vector3 &other) const
    {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3 &other) const
    {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator*(const float number) const
    {
        return Vector3(x * number, y * number, z * number);
    }

    Vector3 operator/(const float number) const
    {
        if (number == 0)
        {
            throw std::invalid_argument("Can't divide by zero.\n");
        }

        return Vector3(x / number, y / number, z / number);
    }

    static Vector3 Lerp(const Vector3 &start, const Vector3 &destination,
                        const float t)
    {
        return LerpUnclamped(start, destination, std::clamp<float>(t, 0, 1));
    }

    static Vector3 LerpUnclamped(const Vector3 &start,
                                 const Vector3 &destination, const float t)
    {
        auto newPosition = Vector3(start);

        newPosition.x += (destination.x - start.x) * t;
        newPosition.y += (destination.y - start.y) * t;
        newPosition.z += (destination.z - start.z) * t;

        return newPosition;
    }

    SDL_FPoint ToFPoint() const { return {x, y}; }

    SDL_FRect ToFRect() const { return {x, y}; }
};
