#pragma once
#ifndef DRACO2D_OBJECT_RECTANGLE_H
#define DRACO2D_OBJECT_RECTANGLE_H

#include "../Base/BaseObject.hpp"

class Rectangle : public BaseObject
{
    SDL_FRect _rect;

public:
    /**
     * @brief Constructs a new Rectangle instance with default dimensions.
     */
    Rectangle(const float x = 470.f,
              const float y = 285.f,
              const float w = 300.f,
              const float h = 150.f)
        : _rect{x, y, w, h}
    {}

    /**
     * @brief Destructor for the Rectangle class.
     */
    ~Rectangle() override = default;

    /**
     * @brief Renders the rectangle outline using the SDL3 renderer API.
     *
     * @param renderer Pointer to the SDL renderer used to draw the rectangle.
     */
    void render(SDL_Renderer* renderer) const override;
};

#endif  // !DRACO2D_OBJECT_RECTANGLE_H