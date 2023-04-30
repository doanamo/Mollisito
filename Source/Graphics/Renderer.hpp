#pragma once

#include "Graphics/Texture.hpp"
#include "Graphics/Rasterizer.hpp"

namespace Graphics
{
    class Renderer
    {
    public:
        struct SetupInfo
        {
            Texture::BufferInfo frameBuffer;
        };

    public:
        Renderer() = default;
        ~Renderer() = default;

        bool Setup(const SetupInfo& info);
        bool Resize(const Texture::BufferInfo& info);
        void ClearFrame(const Math::Vec4f& color);

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
