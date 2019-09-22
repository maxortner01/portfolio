#pragma once

namespace pcs
{
    struct Color
    {
        union
        {
            struct 
            {
                float c[4];
            };

            struct 
            {
                float r, g, b, a;
            };
        };

        Color(float _r = 0.f, float _g = 0.f, float _b = 0.f, float _a = 0.f) :
            r(_r), g(_g), b(_b), a(_a)
        {

        }

        explicit Color(int _r = 0, int _g = 0, int _b = 0, int _a = 0) :
            r((float)_r / 255.f), g((float)_g / 255.f), b((float)_b / 255.f), a((float)_a / 255.f)
        {

        }
    };
}