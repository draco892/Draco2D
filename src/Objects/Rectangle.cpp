#include "Objects/Rectangle.hpp"
#include <algorithm>
#include <cmath>

namespace {
void advance(float& position, float& velocity, float size, float boundary, float seconds)
{
    const float limit = std::max(0.0f, boundary - size);
    if (limit == 0) { position = 0; return; }
    position = std::clamp(position, 0.0f, limit);
    // Fold movement into the interval, retaining overshoot even after multiple bounces.
    const float phase = std::fmod(position + velocity * seconds, 2.0f * limit);
    const float folded = phase < 0 ? phase + 2.0f * limit : phase;
    if (folded > limit) { position = 2.0f * limit - folded; velocity = -velocity; }
    else position = folded;
    if (position == 0) velocity = std::abs(velocity);
    if (position == limit) velocity = -std::abs(velocity);
}
}

Rectangle::Rectangle(const RectangleSettings& settings)
    : _rect(settings.bounds), _color(settings.color), _vx(settings.vx), _vy(settings.vy)
{}

void Rectangle::render(SDL_Renderer* renderer) const
{
    SDL_SetRenderDrawColor(renderer, _color.r, _color.g, _color.b, _color.a);
    SDL_RenderRect(renderer, &_rect);
}

void Rectangle::update(const UpdateContext& context)
{
    advance(_rect.x, _vx, _rect.w, context.width, context.seconds);
    advance(_rect.y, _vy, _rect.h, context.height, context.seconds);
}
