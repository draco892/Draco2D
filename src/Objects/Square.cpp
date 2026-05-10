#include "../include/Objects/Square.hpp"

// Constructor initializes a square centered at (640, 360)
// with side length 200.
Square::Square()
{
    _rect.x = 540.0f;
    _rect.y = 260.0f;
    _rect.w = 200.0f;
    _rect.h = 200.0f;
}

// Render the square outline using SDL3.
void Square::render(SDL_Renderer* renderer) const
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderRect(renderer, &_rect);
}