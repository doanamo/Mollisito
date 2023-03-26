#include "Shared.hpp"
#include "Graphics/Clipper.hpp"

namespace Graphics
{
    void Clipper::SetScissor(int x, int y, int width, int height)
    {
        m_scissor = { x, y, x + width, y + height };
    }

    void Clipper::EnableScissor(bool enable)
    {
        m_scissorEnabled = enable;
    }

    bool Clipper::ClipPixel(int x, int y) const
    {
        if(m_scissorEnabled)
        {
            if(x < m_scissor.x || y < m_scissor.y ||
                x >= m_scissor.z || y >= m_scissor.w)
            {
                return true;
            }
        }

        return false;
    }
}
