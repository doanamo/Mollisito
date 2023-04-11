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
}
