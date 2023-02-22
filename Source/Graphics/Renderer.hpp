#pragma once

#include "Graphics/Texture.hpp"

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
        void ClearFrame();

        void DrawLine(const Math::Vector2f& beginPosition, const Math::Vector2f& endPosition,
            const Math::Color4f& beginColor, const Math::Color4f& endColor);

        Graphics::Texture& GetFrame()
        {
            return m_frame;
        }

    private:
        Graphics::Texture m_frame;
    };
}
