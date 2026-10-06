#pragma once
#include "Base/BaseObject.hpp"
#include "Configuration/ConfigManager.hpp"

class Triangle : public BaseObject
{
public:
    explicit Triangle(const TriangleSettings& settings = {}, const InputSettings& input = {});
    void update(const UpdateContext& context) override;
    void render(SDL_Renderer* renderer) const override;
    const SDL_FRect& bounds() const { return _bounds; }

private:
    SDL_FRect _bounds;
    SDL_Color _color;
    float _speed;
    InputSettings _input;
};
