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

        Texture& GetFrame()
        {
            return m_frame;
        }

        Clipper& GetClipper()
        {
            return m_clipper;
        }

        Rasterizer& GetRasterizer()
        {
            return m_rasterizer;
        }

    private:
        Texture m_frame;
        Clipper m_clipper;
        Rasterizer m_rasterizer;
    };
}
