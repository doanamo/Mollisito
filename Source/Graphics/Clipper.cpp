#include "Shared.hpp"
#include "Graphics/Clipper.hpp"

namespace Graphics
{
    void Clipper::SetViewport(int x, int y, int width, int height)
    {
        m_viewport = { x, y, x + width, y + height };
    }

    bool Clipper::ClipPixel(int x, int y) const
    {
        return x < m_viewport.x || y < m_viewport.y ||
            x >= m_viewport.z || y >= m_viewport.w;
    }
}
