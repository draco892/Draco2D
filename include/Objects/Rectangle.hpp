#pragma once
#include "Base/BaseObject.hpp"
#include "Configuration/ConfigManager.hpp"

class Rectangle : public BaseObject
{
public:
    explicit Rectangle(const RectangleSettings& settings = {});
    void update(const UpdateContext& context) override;
    void render(SDL_Renderer* renderer) const override;
    const SDL_FRect& bounds() const { return _rect; }

private:
    SDL_FRect _rect;
    SDL_Color _color;
    float _vx;
    float _vy;
};
