#include "../include/Objects/Triangle.hpp"

// Render the triangle outline.
void Triangle::render(SDL_Renderer* renderer) const
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderLines(renderer, _vertices, 4);
}