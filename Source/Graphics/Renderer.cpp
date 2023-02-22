#include "Shared.hpp"
#include "Renderer.hpp"

bool Graphics::Renderer::Setup(const SetupInfo& info)
{
    // Create frame texture
    if(!m_frame.Setup(info.windowWidth, info.windowHeight,
        Graphics::Texture::ChannelType::Uint8, 4))
    {
        LOG_ERROR("Failed to create frame texture");
        return false;
    }

    return true;
}

void Graphics::Renderer::ClearFrame()
{
    m_frame.Clear(Math::Color4f(0.0f, 0.0f, 0.0f, 0.0f));
}

void Graphics::Renderer::DrawLine(
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
        m_frame.SetPixel((int)(position.x + 0.5f),
            (int)(position.y + 0.5f), color);
    }
}
