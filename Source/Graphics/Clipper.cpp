#include "Shared.hpp"
#include "Graphics/Clipper.hpp"

void Graphics::Clipper::SetScissor(int x, int y, int width, int height)
{
    m_scissor = { x, y, x + width, y + height };
}

void Graphics::Clipper::EnableScissor(bool enable)
{
    m_scissorEnabled = enable;
}
