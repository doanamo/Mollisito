#pragma once

namespace Math
{
    struct Color
    {
        Color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f)
            : r(r), g(g), b(b), a(a)
        {
        }

        union
        {
            struct
            {
                float r;
                float g;
                float b;
                float a;
            };

            float rgba[4];
        };
    };
}
