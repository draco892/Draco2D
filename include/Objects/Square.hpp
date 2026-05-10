#ifndef DRACO2D_OBJECT_SQUARE_H
#define DRACO2D_OBJECT_SQUARE_H

#include "../Base/BaseObject.hpp"

class Square : public BaseObject
{
    SDL_FRect _rect;

public:
    /**
     * @brief Constructs a new Square instance with default dimensions.
     */
    Square(const float x = 540.f,
           const float y = 260.f,
           const float l = 200.f)
        : _rect{x, y, l, l}
    {}

    /**
     * @brief Destructor for the Square class.
     */
    ~Square() override = default;

    /**
     * @brief Renders the square outline using the SDL3 renderer API.
     *
     * @param renderer Pointer to the SDL renderer used to draw the square.
     */
    void render(SDL_Renderer* renderer) const override;
};

#endif  // !DRACO2D_OBJECT_SQUARE_H