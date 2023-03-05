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

    // Set default viewport
    m_rasterizer.GetClipper().SetViewport(
        0, 0, info.windowWidth, info.windowHeight);

    return true;
}

void Graphics::Renderer::ClearFrame()
{
    m_frame.Clear(Math::Vector4f(0.0f, 0.0f, 0.0f, 0.0f));
}
