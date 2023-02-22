#include "Shared.hpp"
#include "Application.hpp"
#include "Math/Color.hpp"

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
    m_renderer.DrawLine(
        Math::Vector2f(50.0f, 50.0f), Math::Vector2f(300.0f, 200.0f),
        Math::Color4f(1.0f, 0.0f, 0.0f), Math::Color4f(0.0f, 1.0f, 0.0f));
}
