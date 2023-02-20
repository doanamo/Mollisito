#include "Shared.hpp"
#include "Application.hpp"
#include "Math/Color.hpp"

bool Application::Setup(const SetupInfo& info)
{
    // Create frame texture
    if(!m_frame.Setup(info.windowWidth, info.windowHeight,
        Render::Texture::ChannelType::Uint8, 3))
    {
        LOG_ERROR("Failed to create frame texture");
        return false;
    }

    return true;
}

void Application::OnFrame(float deltaTime)
{
    m_frame.Clear(Math::Color(0.0f, 0.5f, 0.5f));
}
