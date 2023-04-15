#include "Shared.hpp"
#include "Application.hpp"

bool Application::Setup(const SetupInfo& info)
{
    // Setup renderer
    Graphics::Renderer::SetupInfo rendererSetup;
    rendererSetup.windowWidth = info.windowWidth;
    rendererSetup.windowHeight = info.windowHeight;

    if(!m_renderer.Setup(rendererSetup))
    {
        LOG_ERROR("Failed to setup renderer");
        return false;
    }

    return true;
}

void Application::OnFrame(float deltaTime)
{
    m_renderer.ClearFrame();
}

bool Application::OnResize(int windowWidth, int windowHeight)
{
    if(!m_renderer.Resize(windowWidth, windowHeight))
        return false;

    return true;
}
