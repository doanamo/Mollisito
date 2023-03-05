#include "Shared.hpp"
#include "Rasterizer.hpp"
#include "Texture.hpp"

namespace Graphics
{
    void Rasterizer::DrawLine2D(Texture& texture,
        const Math::Vec2f& beginPosition, const Math::Vec2f& endPosition,
        const Math::Vec4f& beginColor, const Math::Vec4f& endColor)
    {
        Math::Vec2f positionDiff = endPosition - beginPosition;
        Math::Vec4f colorDiff = endColor - beginColor;

        auto segments = (int)(std::max(
            std::abs(positionDiff.x),
            std::abs(positionDiff.y)));

        float segmentInv = 1.0f / (float)segments;
        for(int i = 0; i <= segments; ++i)
        {
            float alpha = (float)i * segmentInv;
            Math::Vec2f position = Math::LerpDiff(beginPosition, positionDiff, alpha);
            Math::Vec4f color = Math::LerpDiff(beginColor, colorDiff, alpha);

            if(m_clipper.ClipPixel((int)position.x, (int)position.y))
            {
                continue;
            }

            texture.SetPixel((int)position.x, (int)position.y, color);
        }
    }
}
