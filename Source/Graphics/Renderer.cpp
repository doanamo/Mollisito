#include "Shared.hpp"
#include "Renderer.hpp"

bool Graphics::Renderer::Setup(const SetupInfo& info)
{
    // Create frame texture
    Texture::SetupInfo frameInfo;
    frameInfo.buffer = info.frameBuffer;
    frameInfo.channelType = Graphics::Texture::ChannelType::Uint8;
    frameInfo.channelCount = 4;

    if(!m_frame.Setup(frameInfo))
    {
        LOG_ERROR("Failed to create frame texture");
        return false;
    }

    return true;
}

bool Graphics::Renderer::Resize(const Texture::BufferInfo& info)
{
    if(!m_frame.Resize(info))
    {
        LOG_ERROR("Failed to resize frame texture");
        return false;
    }

    return true;
}

void Graphics::Renderer::ClearFrame(const Math::Vec4f& color)
{
    m_frame.Clear(color);
}
