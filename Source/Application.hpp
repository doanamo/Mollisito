#pragma once

#include "Render/Texture.hpp"

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

    Render::Texture& GetFrame()
    {
        return m_frame;
    }

private:
    Render::Texture m_frame;
};
