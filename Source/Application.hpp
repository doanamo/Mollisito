#pragma once

#include "Graphics/Renderer.hpp"

class Application
{
public:
    Application() = default;
    ~Application() = default;

    struct SetupInfo
    {
        int windowWidth = 0;
        int windowHeight = 0;
    };

    bool Setup(const SetupInfo& info);
    void OnFrame(float deltaTime);
    bool OnResize(int windowWidth, int windowHeight);

    Graphics::Renderer& GetRenderer()
    {
        return m_renderer;
    }

private:
    Graphics::Renderer m_renderer;
};
