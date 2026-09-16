#pragma once
#ifndef DRACO2D_OBJECT_TRIANGLE_H
#define DRACO2D_OBJECT_TRIANGLE_H
#include "../Base/BaseObject.hpp"
#include <algorithm>

class Triangle : public BaseObject
{
    SDL_FPoint _vertices[4]; // Last point repeats the first one to close the triangle
    SDL_FRect _bounding_box;
    float _vx;
    float _vy;

public:
    /**
     * @brief Constructs a new Triangle instance with default vertices.
     */
    Triangle(const SDL_FPoint topVertex = {640.0f, 100.0f},
              const SDL_FPoint botLeftVertex = {240.0f, 520.0f},
              const SDL_FPoint botRightVertex = {1040.0f, 520.0f})
        : _vertices{topVertex, botLeftVertex, botRightVertex, topVertex},
          _vx(2.0f), _vy(2.0f)
    {
        _bounding_box.x = std::min({topVertex.x, botLeftVertex.x, botRightVertex.x});
        _bounding_box.y = std::min({topVertex.y, botLeftVertex.y, botRightVertex.y});
        _bounding_box.w = std::max({topVertex.x, botLeftVertex.x, botRightVertex.x}) - _bounding_box.x;
        _bounding_box.h = std::max({topVertex.y, botLeftVertex.y, botRightVertex.y}) - _bounding_box.y;
    }
    
    /**
     * @brief Destructor for the Triangle class.
     */
    ~Triangle() override = default;
  
    /**
     * @brief Renders the triangle outline using the SDL3 renderer API.
     *
     * @param renderer Pointer to the SDL renderer used to draw the triangle.
     */
    void render(SDL_Renderer* renderer) const override;
    /**
     * @brief Updates the triangle's position based on its velocity.
     */
    void update() override;
};
#endif  // !DRACO2D_OBJECT_TRIANGLE_H