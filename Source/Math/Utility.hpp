#pragma once

namespace Math
{
    template<typename Type>
    Type Lerp(const Type& a, const Type& b, float alpha)
    {
        return a + (b - a) * alpha;
    }

    template<typename Type>
    Type LerpDiff(const Type& a, const Type& diff, float alpha)
    {
        return a + diff * alpha;
    }
}
