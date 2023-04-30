#include "Shared.hpp"
#include "Application.hpp"

bool Application::Setup(const SetupInfo& info)
{
    if(!m_renderer.Setup(info.renderer))
    {
        LOG_ERROR("Failed to setup renderer");
        return false;
    }

    return true;
}

void Application::OnFrame(float deltaTime)
{
    m_renderer.ClearFrame(Math::Vec4f(0.0f, 0.0f, 0.0f, 0.0f));
}

bool Application::OnResize(const ResizeInfo& info)
{
    Graphics::Texture::BufferInfo frameBufferInfo;
    frameBufferInfo = info.frameBuffer;

    if(!m_renderer.Resize(frameBufferInfo))
        return false;

    return true;
}
