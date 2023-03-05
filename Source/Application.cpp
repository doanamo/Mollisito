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

    // Draw rotating triangle lines
    static float rotationBase = 0.0f;
    rotationBase += Math::Pi / 2.0f * deltaTime;

    float width = (float)m_renderer.GetFrame().GetWidth();
    float height = (float)m_renderer.GetFrame().GetHeight();
    Math::Vector2f position(width / 2.0f, height / 2.0f);

    for(int i = 0; i < 6; ++i)
    {
        const float size = 5.0f + 15.0f * i;
        float rotation = rotationBase + (Math::Pi / 1.52f) * i;

        Math::Vector2f p1(
            position.x + std::cos(rotation - Math::Pi / 6.0f) * size,
            position.y + std::sin(rotation - Math::Pi / 6.0f) * size);

        Math::Vector2f p2(
            position.x + std::cos(rotation + Math::Pi / 2.0f) * size,
            position.y + std::sin(rotation + Math::Pi / 2.0f) * size);

        Math::Vector2f p3(
            position.x + std::cos(rotation + Math::Pi + Math::Pi / 6.0f) * size,
            position.y + std::sin(rotation + Math::Pi + Math::Pi / 6.0f) * size);

        auto c1 = Math::Color4f(std::max(0.0f, 1.0f - 0.02f * i), 0.0f, 0.0f);
        auto c2 = Math::Color4f(0.0f, std::max(0.0f, 1.0f - 0.02f * i), 0.0f);
        auto c3 = Math::Color4f(0.0f, 0.0f, std::max(0.0f, 1.0f - 0.02f * i));

        m_renderer.DrawLine(p1, p2, c1, c2);
        m_renderer.DrawLine(p2, p3, c2, c3);
        m_renderer.DrawLine(p3, p1, c3, c1);
    }
}
