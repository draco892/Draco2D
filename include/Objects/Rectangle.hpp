#pragma once
#ifndef DRACO2D_OBJECT_RECTANGLE_H
#define DRACO2D_OBJECT_RECTANGLE_H

#include "../Base/BaseObject.hpp"

class Rectangle : public BaseObject
{
    SDL_FRect _rect;
    float _vx;
    float _vy;

public:
    /**
     * @brief Constructs a new Rectangle instance with default dimensions.
     *
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     * @param w The width.
     * @param h The height.
     * @param vx The horizontal velocity.
     * @param vy The vertical velocity.
     */
    Rectangle(const float x = 470.f,
               const float y = 285.f,
               const float w = 300.f,
               const float h = 150.f,
               const float vx = 2.0f,
               const float vy = 2.0f)
        : _rect{x, y, w, h}, _vx(vx), _vy(vy)
    {}
    
    /**
     * @brief Destructor for the Rectangle class.
     */
    ~Rectangle() override = default;
    
    /**
     * @brief Updates the rectangle's position based on its velocity.
     */
    void update() override;

    /**
     * @brief Renders the rectangle outline using the SDL3 renderer API.
     *
     * @param renderer Pointer to the SDL renderer used to draw the rectangle.
     */
    void render(SDL_Renderer* renderer) const override;
};

#endif  // !DRACO2D_OBJECT_RECTANGLE_H
