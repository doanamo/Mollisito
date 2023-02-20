#include "Shared.hpp"
#include "Renderer.hpp"

bool Graphics::Renderer::Setup(const SetupInfo& info)
{
    // Create frame texture
    if(!m_frame.Setup(info.windowWidth, info.windowHeight,
        Graphics::Texture::ChannelType::Uint8, 3))
    {
        LOG_ERROR("Failed to create frame texture");
        return false;
    }

    return true;
}

void Graphics::Renderer::OnFrame(float deltaTime)
{
    m_frame.Clear(Math::Color4b(0, 128, 128));
}
