#include "../include/Objects/Square.hpp"

// Render the square outline using SDL3.
void Square::render(SDL_Renderer* renderer) const
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderRect(renderer, &_rect);
}

void Square::update()
{
    _rect.x += _vx;
    _rect.y += _vy;
    
    if (_rect.x < 0 || _rect.x + _rect.w > 1280)
    {
        _vx = -_vx;
    }
    if (_rect.y < 0 || _rect.y + _rect.h > 720)
    {
        _vy = -_vy;
    }
}
