#include "../include/Objects/Rectangle.hpp"

// Constructor initializes a rectangle centered at (640, 360)
// with width 300 and height 150.
Rectangle::Rectangle()
{
    _rect.x = 470.0f;
    _rect.y = 285.0f;
    _rect.w = 300.0f;
    _rect.h = 150.0f;
}

// Render the rectangle outline.
void Rectangle::render(SDL_Renderer* renderer) const
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderRect(renderer, &_rect);
}