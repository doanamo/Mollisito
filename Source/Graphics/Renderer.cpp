#include "Shared.hpp"
#include "Renderer.hpp"

bool Graphics::Renderer::Setup(const SetupInfo& info)
{
    // Create frame color texture
    Texture::SetupInfo frameColorInfo;
    frameColorInfo.format = Format::R8G8B8A8_UINT;
    frameColorInfo.imageBuffers = { info.frameBuffer };

    if(!m_frameColor.Setup(frameColorInfo))
    {
        LOG_ERROR("Failed to create frame color texture");
        return false;
    }

    // Create frame depth texture
    Image::BufferInfo frameDepthBufferInfo;
    frameDepthBufferInfo.width = info.frameBuffer.width;
    frameDepthBufferInfo.height = info.frameBuffer.height;

    Texture::SetupInfo frameDepthInfo;
    frameDepthInfo.format = Format::R32_FLOAT;
    frameDepthInfo.imageBuffers = { frameDepthBufferInfo };

    if(!m_frameDepth.Setup(frameDepthInfo))
    {
        LOG_ERROR("Failed to create frame depth texture");
        return false;
    }

    return true;
}

bool Graphics::Renderer::Resize(const Image::BufferInfo& info)
{
    // Resize frame color texture
    if(!m_frameColor.Resize({ info }))
    {
        LOG_ERROR("Failed to resize frame color texture");
        return false;
    }

    // Resize frame depth texture
    Image::BufferInfo frameDepthBufferInfo;
    frameDepthBufferInfo.width = info.width;
    frameDepthBufferInfo.height = info.height;

    if(!m_frameDepth.Resize({ frameDepthBufferInfo }))
    {
        LOG_ERROR("Failed to resize frame depth texture");
        return false;
    }

    return true;
}

void Graphics::Renderer::ClearFrame(const Math::Vec4f& color, float depth)
{
    m_frameColor.Clear(color);
    m_frameDepth.Clear(depth);
}
