#pragma once

#include "Graphics/Texture.hpp"
#include "Graphics/Rasterizer.hpp"

namespace Graphics
{
    class Renderer
    {
    public:
        Renderer() = default;
        ~Renderer() = default;

        struct SetupInfo
        {
            int windowWidth = 0;
            int windowHeight = 0;
        };

        bool Setup(const SetupInfo& info);
        bool Resize(int windowWidth, int windowHeight);
        void ClearFrame();

        Graphics::Texture& GetFrame()
        {
            return m_frame;
        }

        Graphics::Rasterizer& GetRasterizer()
        {
            return m_rasterizer;
        }

    private:
        Graphics::Texture m_frame;
        Graphics::Rasterizer m_rasterizer;
    };
}
