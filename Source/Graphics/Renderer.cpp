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

bool Graphics::Renderer::Resize(int windowWidth, int windowHeight)
{
    // Resize frame texture
    if(!m_frame.Resize(windowWidth, windowHeight))
    {
        LOG_ERROR("Failed to resize frame texture");
        return false;
    }

    return true;
}

void Graphics::Renderer::ClearFrame()
{
    m_frame.Clear(Math::Vec4f(0.0f, 0.0f, 0.0f, 0.0f));
}
