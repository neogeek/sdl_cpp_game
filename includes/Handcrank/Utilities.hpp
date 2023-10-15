// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include <string>

namespace Handcrank
{

class Utilities
{
  public:
    static std::string LeftPad(const std::string &content, const char pad,
                               int length)
    {
        return std::string(length - content.size(), pad) + content;
    }

    static std::string RightPad(const std::string &content, const char pad,
                                int length)
    {
        return content + std::string(length - content.size(), pad);
    }
};

} // namespace Handcrank
