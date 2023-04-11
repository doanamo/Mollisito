#pragma once

#include "Graphics/Clipper.hpp"

namespace Graphics
{
    class Texture;

    class Rasterizer : private Common::NonCopyable
    {
    public:
        Rasterizer() = default;
        ~Rasterizer() = default;

        void DrawLine(Texture& texture,
            const Math::Vec2f& beginPosition, const Math::Vec2f& endPosition,
            const Math::Vec4f& beginColor, const Math::Vec4f& endColor);
    };
}
