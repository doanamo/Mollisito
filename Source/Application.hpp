#pragma once

#include "Graphics/Renderer.hpp"

class Application
{
public:
    struct SetupInfo
    {
        Graphics::Renderer::SetupInfo renderer;
    };

    struct ResizeInfo
    {
        Graphics::Image::BufferInfo frameBuffer;
    };

public:
    Application() = default;
    ~Application() = default;

    bool Setup(const SetupInfo& info);
    void OnFrame(float deltaTime);
    bool OnResize(const ResizeInfo& info);

    Graphics::Renderer& GetRenderer()
    {
        return m_renderer;
    }

private:
    Graphics::Renderer m_renderer;
};
