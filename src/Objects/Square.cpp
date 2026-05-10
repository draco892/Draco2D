#include "../include/Objects/Square.hpp"

// Render the square outline using SDL3.
void Square::render(SDL_Renderer* renderer) const
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderRect(renderer, &_rect);
}