#pragma once

namespace Math
{
    struct Vector2f
    {
        Vector2f() = default;
        Vector2f(float x, float y)
            : x(x)
            , y(y)
        {
        }

        Vector2f operator+(const Vector2f& other) const
        {
            return Vector2f(x + other.x, y + other.y);
        }

        Vector2f operator-(const Vector2f& other) const
        {
            return Vector2f(x - other.x, y - other.y);
        }

        Vector2f operator*(float value) const
        {
            return Vector2f(x * value, y * value);
        }

        Vector2f operator/(float value) const
        {
            return Vector2f(x / value, y / value);
        }

        float x;
        float y;
    };

    struct Vector3f
    {
        Vector3f() = default;
        Vector3f(float x, float y, float z)
            : x(x)
            , y(y)
            , z(z)
        {
        }

        Vector3f operator+(const Vector3f& other) const
        {
            return Vector3f(x + other.x, y + other.y, z + other.z);
        }

        Vector3f operator-(const Vector3f& other) const
        {
            return Vector3f(x - other.x, y - other.y, z - other.z);
        }

        Vector3f operator*(float value) const
        {
            return Vector3f(x * value, y * value, z * value);
        }

        Vector3f operator/(float value) const
        {
            return Vector3f(x / value, y / value, z / value);
        }

        float x;
        float y;
        float z;
    };
}
