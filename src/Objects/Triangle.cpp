#include "Objects/Triangle.hpp"
#include <algorithm>
#include <cmath>

Triangle::Triangle(const TriangleSettings& settings, const InputSettings& input)
    : _bounds(settings.bounds), _color(settings.color), _speed(settings.speed), _input(input)
{}

void Triangle::render(SDL_Renderer* renderer) const
{
    const SDL_FPoint top{_bounds.x + _bounds.w / 2, _bounds.y};
    const SDL_FPoint vertices[]{top, {_bounds.x, _bounds.y + _bounds.h},
                               {_bounds.x + _bounds.w, _bounds.y + _bounds.h}, top};
    SDL_SetRenderDrawColor(renderer, _color.r, _color.g, _color.b, _color.a);
    SDL_RenderLines(renderer, vertices, 4);
}

void Triangle::update(const UpdateContext& context)
{
    float dx = 0, dy = 0;
    if (context.keyboard) {
        dx = static_cast<float>(context.keyboard[_input.right]) - context.keyboard[_input.left];
        dy = static_cast<float>(context.keyboard[_input.down]) - context.keyboard[_input.up];
    }
    const float length = std::sqrt(dx * dx + dy * dy);
    if (length > 0) {
        _bounds.x += dx / length * _speed * context.seconds;
        _bounds.y += dy / length * _speed * context.seconds;
    }
    _bounds.x = std::clamp(_bounds.x, 0.0f, std::max(0.0f, context.width - _bounds.w));
    _bounds.y = std::clamp(_bounds.y, 0.0f, std::max(0.0f, context.height - _bounds.h));
}
