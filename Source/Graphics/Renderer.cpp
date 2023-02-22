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
    Math::Vector2f vector = endPosition - beginPosition;
    int segments = (int)(std::max(std::abs(vector.x), std::abs(vector.y)) + 0.5f);

    for(int i = 0; i <= segments; ++i)
    {
        float alpha = (float)i / (float)segments;
        Math::Vector2f position = beginPosition + vector * alpha;
        Math::Color4f color = Math::Lerp(beginColor, endColor, alpha);
        m_frame.SetPixel((int)(position.x + 0.5f), (int)(position.y + 0.5f), color);
    }
}
