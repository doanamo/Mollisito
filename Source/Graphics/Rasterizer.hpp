#pragma once

#include "Graphics/Clipper.hpp"

namespace Graphics
{
    class Texture;

    class Rasterizer : private Common::NonCopyable
    {
    public:
        Rasterizer() = default;
        ~Rasterizer() = default;
    };
}
