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
            Image::BufferInfo frameBuffer;
        };

    public:
        Renderer() = default;
        ~Renderer() = default;

        bool Setup(const SetupInfo& info);
        bool Resize(const Image::BufferInfo& info);
        void ClearFrame(const Math::Vec4f& color, float depth);

        Texture& GetFrameColor()
        {
            return m_frameColor;
        }

        Texture& GetFrameDepth()
        {
            return m_frameDepth;
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
        Texture m_frameColor;
        Texture m_frameDepth;

        Clipper m_clipper;
        Rasterizer m_rasterizer;
    };
}
