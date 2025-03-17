// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include <algorithm>
#include <string>

namespace Handcrank
{

inline std::string LeftPad(const std::string &content, const char pad,
                           int length)
{
    return std::string(length - content.size(), pad) + content;
}

inline std::string RightPad(const std::string &content, const char pad,
                            int length)
{
    return content + std::string(length - content.size(), pad);
}

inline float Lerp(float a, float b, float t) { return (1 - t) * a + b * t; }

inline float InverseLerp(float a, float b, float v)
{
    return std::clamp(((v - a) / (b - a)), 0.0f, 1.0f);
}

inline int randomNumberRange(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

inline bool randomBoolean() { return rand() > (RAND_MAX / 2); }

} // namespace Handcrank
