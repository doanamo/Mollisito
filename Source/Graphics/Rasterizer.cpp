#include "Shared.hpp"
#include "Rasterizer.hpp"
#include "Texture.hpp"

namespace Graphics
{
    void Rasterizer::DrawLine(Texture& texture,
        const Math::Vec2f& beginPosition, const Math::Vec2f& endPosition,
        const Math::Vec4f& beginColor, const Math::Vec4f& endColor)
    {
        Math::Vec2f positionDiff = endPosition - beginPosition;
        Math::Vec4f colorDiff = endColor - beginColor;

        int segments = (int)(std::max(
            std::abs(positionDiff.x),
            std::abs(positionDiff.y)));

        for(int i = 0; i <= segments; ++i)
        {
            float alpha = (float)i / (float)segments;
            Math::Vec2f position = beginPosition + positionDiff * alpha;
            Math::Vec4f color = beginColor + colorDiff * alpha;

            if(m_clipper.ClipPixel((int)position.x, (int)position.y))
            {
                continue;
            }

            texture.SetPixel((int)position.x, (int)position.y, color);
        }
    }
}
