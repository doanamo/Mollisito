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
            const Math::Vector2f& beginPosition, const Math::Vector2f& endPosition,
            const Math::Vector4f& beginColor, const Math::Vector4f& endColor);

        Clipper& GetClipper()
        {
            return m_clipper;
        }

    private:
        Clipper m_clipper;
    };
}
