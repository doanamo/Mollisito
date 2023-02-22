#pragma once

namespace Math
{
    struct Color4f
    {
        Color4f()
            : r(0.0f)
            , g(0.0f)
            , b(0.0f)
            , a(1.0f)
        {
        }

        Color4f(float r, float g = 0.0f, float b = 0.0f, float a = 1.0f)
            : r(r)
            , g(g)
            , b(b)
            , a(a)
        {
        }

        bool IsUniform() const
        {
            return r == g && r == b && r == a;
        }

        uint32_t ToUint32() const
        {
            return (uint8_t)(r * 255.0f + 0.5f)
                | (uint8_t)(g * 255.0f + 0.5f) << 8
                | (uint8_t)(b * 255.0f + 0.5f) << 16
                | (uint8_t)(a * 255.0f + 0.5f) << 24;
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

            float array[4];
        };
    };

    inline Color4f Lerp(const Color4f& a, const Color4f& b, float alpha)
    {
        Color4f result;
        result.r = a.r + (b.r - a.r) * alpha;
        result.g = a.g + (b.g - a.g) * alpha;
        result.b = a.b + (b.b - a.b) * alpha;
        result.a = a.a + (b.a - a.a) * alpha;
        return result;
    }
}
