#pragma once
#include "Objects/Rectangle.hpp"

class Square : public Rectangle
{
public:
    explicit Square(const RectangleSettings& settings = EngineConfig{}.square);
};
