#pragma once

namespace Graphics
{
    class Clipper : private Common::NonCopyable
    {
    public:
        Clipper() = default;
        ~Clipper() = default;

        void SetScissor(int x, int y, int width, int height);
        void EnableScissor(bool enable);

    private:
        Math::Vec4i m_scissor;
        bool m_scissorEnabled = false;
    };
}
