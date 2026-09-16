#pragma once
#ifndef DRACO2D_BASE_BASECOLOR_H
#define DRACO2D_BASE_BASECOLOR_H

#include <cstdint>


namespace Draco2D::Base {

    struct Color
    {
        uint8_t r, g, b, a;

        constexpr Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a = 255)
            : r(_r)
            , g(_g)
            , b(_b)
            , a(_a)
        {}
    };

    struct ColorFloat
    {
        float rf, gf, bf, af;

        constexpr ColorFloat(float _rf, float _gf, float _bf, float _af = 1.0f)
            : rf(_rf)
            , gf(_gf)
            , bf(_bf)
            , af(_af)
        {}
    };

    // Now the compiler can easily resolve these because the constructor is clear
    static constexpr Color red{255, 0, 0, 255};
    static constexpr Color green{0, 255, 0, 255};
    static constexpr Color blue{0, 0, 255, 255};
    static constexpr Color white{255, 255, 255, 255};
    static constexpr Color black{0, 0, 0, 255};

} // namespace Draco2D::Base

#endif  // !DRACO2D_BASE_BASECOLOR_H
