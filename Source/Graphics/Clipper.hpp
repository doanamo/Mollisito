#pragma once

namespace Graphics
{
    class Clipper : private Common::NonCopyable
    {
    public:
        Clipper() = default;
        ~Clipper() = default;

        void SetViewport(int x, int y, int width, int height);
        bool ClipPixel(int x, int y) const;

    private:
        Math::Vec4i m_viewport;
    };
}
