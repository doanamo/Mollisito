#pragma once

namespace Math
{
    template<typename Type>
    struct Vector2
    {
        Vector2() = default;
        Vector2(Type x, Type y)
            : x(x)
            , y(y)
        {
        }

        Vector2 operator+(const Vector2& other) const
        {
            return Vector2(x + other.x, y + other.y);
        }

        Vector2 operator-(const Vector2& other) const
        {
            return Vector2(x - other.x, y - other.y);
        }

        Vector2 operator*(Type value) const
        {
            return Vector2(x * value, y * value);
        }

        Vector2 operator/(Type value) const
        {
            return Vector2(x / value, y / value);
        }

        bool IsUniform() const
        {
            return x == y;
        }

        Type x;
        Type y;
    };

    using Vector2i = Vector2<int>;
    using Vector2f = Vector2<float>;

    template<typename Type>
    struct Vector3
    {
        Vector3() = default;
        Vector3(Type x, Type y, Type z)
            : x(x)
            , y(y)
            , z(z)
        {
        }

        Vector3 operator+(const Vector3& other) const
        {
            return Vector3(x + other.x, y + other.y, z + other.z);
        }

        Vector3 operator-(const Vector3& other) const
        {
            return Vector3(x - other.x, y - other.y, z - other.z);
        }

        Vector3 operator*(Type value) const
        {
            return Vector3(x * value, y * value, z * value);
        }

        Vector3 operator/(Type value) const
        {
            return Vector3(x / value, y / value, z / value);
        }

        bool IsUniform() const
        {
            return x == y && x == z;
        }

        union
        {
            struct  
            {
                Type x;
                Type y;
                Type z;
            };

            struct
            {
                Type r;
                Type g;
                Type b;
            };

            Type array[3];
        };
    };

    using Vector3i = Vector3<int>;
    using Vector3f = Vector3<float>;

    template<typename Type>
    struct Vector4
    {
        Vector4() = default;
        Vector4(Type x, Type y, Type z, Type w)
            : x(x)
            , y(y)
            , z(z)
            , w(w)
        {
        }

        Vector4 operator+(const Vector4& other) const
        {
            return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
        }

        Vector4 operator-(const Vector4& other) const
        {
            return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
        }

        Vector4 operator*(Type value) const
        {
            return Vector4(x * value, y * value, z * value, w * value);
        }

        Vector4 operator/(Type value) const
        {
            return Vector4(x / value, y / value, z / value, w / value);
        }

        bool IsUniform() const
        {
            return x == y && x == z && x == w;
        }

        union
        {
            struct  
            {
                Type x;
                Type y;
                Type z;
                Type w;
            };

            struct
            {
                Type r;
                Type g;
                Type b;
                Type a;
            };

            Type array[4];
        };
    };

    using Vector4i = Vector4<int>;
    using Vector4f = Vector4<float>;

    template<typename Type>
    Type Lerp(const Type& a, const Type& b, float alpha)
    {
        return a + (b - a) * alpha;
    }
}
