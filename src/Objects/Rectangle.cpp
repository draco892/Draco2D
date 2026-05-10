#include "../include/Objects/Rectangle.hpp"


void Rectangle::render(SDL_Renderer* renderer) const
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderRect(renderer, &_rect);
}