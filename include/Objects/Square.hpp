#pragma once
#ifndef DRACO2D_OBJECT_SQUARE_H
#define DRACO2D_OBJECT_SQUARE_H

#include "../Base/BaseObject.hpp"

class Square : public BaseObject
{
    SDL_FRect _rect;
    float _vx;
    float _vy;

public:
    /**
     * @brief Constructs a new Square instance with default dimensions.
     *
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     * @param l The side length.
     * @param vx The horizontal velocity.
     * @param vy The vertical velocity.
     */
    Square(const float x = 540.f,
           const float y = 260.f,
           const float l = 200.f,
           const float vx = 2.0f,
           const float vy = 2.0f)
        : _rect{x, y, l, l}, _vx(vx), _vy(vy)
    {}
    
    /**
     * @brief Destructor for the Square class.
     */
    ~Square() override = default;
    
    /**
     * @brief Updates the square's position based on its velocity.
     */
    void update() override;

    /**
     * @brief Renders the square outline using the SDL3 renderer API.
     *
     * @param renderer Pointer to the SDL renderer used to draw the square.
     */
    void render(SDL_Renderer* renderer) const override;
};

#endif  // !DRACO2D_OBJECT_SQUARE_H
