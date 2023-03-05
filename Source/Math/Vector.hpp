#pragma once

namespace Math
{
    template<typename Type>
    struct Vec2
    {
        Vec2() = default;
        constexpr Vec2(Type x, Type y)
            : x(x), y(y)
        {
        }

        Vec2 operator+(const Vec2& other) const
        {
            return Vec2(x + other.x, y + other.y);
        }

        Vec2 operator-(const Vec2& other) const
        {
            return Vec2(x - other.x, y - other.y);
        }

        Vec2 operator*(Type value) const
        {
            return Vec2(x * value, y * value);
        }

        Vec2 operator/(Type value) const
        {
            return Vec2(x / value, y / value);
        }

        bool IsUniform() const
        {
            return x == y;
        }

        Type x, y;
    };

    using Vec2i = Vec2<int>;
    using Vec2f = Vec2<float>;

    template<typename Type>
    struct Vec3
    {
        Vec3() = default;
        constexpr Vec3(Type x, Type y, Type z)
            : x(x), y(y), z(z)
        {
        }

        Vec3 operator+(const Vec3& other) const
        {
            return Vec3(x + other.x, y + other.y, z + other.z);
        }

        Vec3 operator-(const Vec3& other) const
        {
            return Vec3(x - other.x, y - other.y, z - other.z);
        }

        Vec3 operator*(Type value) const
        {
            return Vec3(x * value, y * value, z * value);
        }

        Vec3 operator/(Type value) const
        {
            return Vec3(x / value, y / value, z / value);
        }

        bool IsUniform() const
        {
            return x == y && x == z;
        }

        union
        {
            struct  
            {
                Type x, y, z;
            };

            struct
            {
                Type r, g, b;
            };

            Type array[3];
        };
    };

    using Vec3i = Vec3<int>;
    using Vec3f = Vec3<float>;

    template<typename Type>
    struct Vec4
    {
        Vec4() = default;
        constexpr Vec4(Type x, Type y, Type z, Type w)
            : x(x), y(y), z(z), w(w)
        {
        }

        Vec4 operator+(const Vec4& other) const
        {
            return Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
        }

        Vec4 operator-(const Vec4& other) const
        {
            return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
        }

        Vec4 operator*(Type value) const
        {
            return Vec4(x * value, y * value, z * value, w * value);
        }

        Vec4 operator/(Type value) const
        {
            return Vec4(x / value, y / value, z / value, w / value);
        }

        bool IsUniform() const
        {
            return x == y && x == z && x == w;
        }

        union
        {
            struct
            {
                Type x, y, z, w;
            };

            struct
            {
                Type r, g, b, a;
            };

            Type array[4];
        };
    };

    using Vec4i = Vec4<int>;
    using Vec4f = Vec4<float>;
}
