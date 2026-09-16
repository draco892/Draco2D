#include "../include/Objects/Rectangle.hpp"


void Rectangle::render(SDL_Renderer* renderer) const
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderRect(renderer, &_rect);
}

void Rectangle::update()
{
    _rect.x += _vx;
    _rect.y += _vy;

    // Simple bouncing logic for 1280x720
    if (_rect.x < 0 || _rect.x + _rect.w > 1280)
    {
        _vx = -_vx;
    }
    if (_rect.y < 0 || _rect.y + _rect.h > 720)
    {
        _vy = -_vy;
    }
}
