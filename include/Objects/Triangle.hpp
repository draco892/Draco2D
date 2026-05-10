#ifndef DRACO2D_OBJECT_TRIANGLE_H
#define DRACO2D_OBJECT_TRIANGLE_H

#include "../Base/BaseObject.hpp"

class Triangle : public BaseObject
{
    SDL_FPoint _vertices[4]; // Last point repeats the first one to close the triangle

public:
    /**
     * @brief Constructs a new Triangle instance with default vertices.
     */
    Triangle();

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
};

#endif  // !DRACO2D_OBJECT_TRIANGLE_H