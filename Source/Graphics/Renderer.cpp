#include "Shared.hpp"
#include "Renderer.hpp"

bool Graphics::Renderer::Setup(const SetupInfo& info)
{
    // Create frame texture
    Texture::SetupInfo frameInfo;
    frameInfo.format = Format::R8G8B8A8_UINT;
    frameInfo.imageBuffers = { info.frameBuffer };

    if(!m_frame.Setup(frameInfo))
    {
        LOG_ERROR("Failed to create frame texture");
        return false;
    }

    return true;
}

bool Graphics::Renderer::Resize(const Image::BufferInfo& info)
{
    Texture::ImageBufferInfos infos = { info };
    if(!m_frame.Resize(infos))
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
