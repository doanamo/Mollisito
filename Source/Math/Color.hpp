#pragma once

namespace Math
{
    struct Color4f;

    struct Color4b
    {
        Color4b()
            : r(0x00)
            , g(0x00)
            , b(0x00)
            , a(0xFF)
        {
        }

        explicit Color4b(uint32_t value)
            : value(value)
        {
        }

        Color4b(uint8_t r, uint8_t g = 0x00, uint8_t b = 0x00, uint8_t a = 0xFF)
            : r(r)
            , g(g)
            , b(b)
            , a(a)
        {
        }

        explicit Color4b(const Color4f& color);

        bool IsUniform() const
        {
            return r == g && r == b && r == a;
        }

        union
        {
            struct
            {
                uint8_t r;
                uint8_t g;
                uint8_t b;
                uint8_t a;
            };

            uint32_t value;
            uint8_t array[4];
        };
    };

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

        explicit Color4f(const Color4b& color);

        bool IsUniform() const
        {
            return r == g && r == b && r == a;
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

    inline Color4b::Color4b(const Color4f& color)
        : r((uint8_t)(color.r * 255.0f + 0.5f))
        , g((uint8_t)(color.g * 255.0f + 0.5f))
        , b((uint8_t)(color.b * 255.0f + 0.5f))
        , a((uint8_t)(color.a * 255.0f + 0.5f))
    {
    }

    inline Color4f::Color4f(const Color4b& color)
        : r(color.r / 255.0f)
        , g(color.g / 255.0f)
        , b(color.b / 255.0f)
        , a(color.a / 255.0f)
    {
    }
}
