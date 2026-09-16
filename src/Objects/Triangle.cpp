#include "../include/Objects/Triangle.hpp"
#include "../include/Base/BaseColor.hpp"

const int points(4);

// Render the triangle outline.
void Triangle::render(SDL_Renderer* renderer) const
{
    SDL_SetRenderDrawColor(renderer,
                            Draco2D::Base::red.r,
                            Draco2D::Base::red.g,
                            Draco2D::Base::red.b,
                            Draco2D::Base::red.a);
    SDL_RenderLines(renderer, _vertices, points);
}

void Triangle::update()
{
    // Update positions
    _bounding_box.x += _vx;
    _bounding_box.y += _vy;

    for (int i = 0; i < 4; ++i) {
        _vertices[i].x += _vx;
        _vertices[i].y += _vy;
    }

    // Simple bouncing logic for 1280x720
    if (_bounding_box.x < 0 || _bounding_box.x + _bounding_box.w > 1280)
    {
        _vx = -_vx;
    }
    if (_bounding_box.y < 0 || _bounding_box.y + _bounding_box.h > 720)
    {
        _vy = -_vy;
    }
}