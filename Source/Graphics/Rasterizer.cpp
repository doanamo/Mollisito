#include "Shared.hpp"
#include "Rasterizer.hpp"
#include "Texture.hpp"

namespace Graphics
{
    void Rasterizer::DrawLine(Texture& texture,
        const Math::Vector2f& beginPosition, const Math::Vector2f& endPosition,
        const Math::Color4f& beginColor, const Math::Color4f& endColor)
    {
        Math::Vector2f positionDiff = endPosition - beginPosition;
        Math::Color4f colorDiff = endColor - beginColor;

        int segments = (int)(std::max(std::abs(positionDiff.x),
            std::abs(positionDiff.y)) + 0.5f);

        for(int i = 0; i <= segments; ++i)
        {
            float alpha = (float)i / (float)segments;
            Math::Vector2f position = beginPosition + positionDiff * alpha;
            Math::Color4f color = beginColor + colorDiff * alpha;
            texture.SetPixel((int)(position.x + 0.5f),
                (int)(position.y + 0.5f), color);
        }
    }
}
