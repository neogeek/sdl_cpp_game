#pragma once

#include <string>

class Utilities
{

  public:
    static std::string LeftPad(std::string content, const char pad, int length)
    {
        return std::string(length - content.size(), pad) + content;
    }

    static std::string RightPad(std::string content, const char pad, int length)
    {
        return content + std::string(length - content.size(), pad);
    }
};
