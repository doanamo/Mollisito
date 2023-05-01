#pragma once

#include "Graphics/Formats.hpp"
#include "Graphics/Image.hpp"

namespace Graphics
{
    class Texture : private Common::NonCopyable
    {
    public:
        using ImageBufferInfos = std::vector<Image::BufferInfo>;

        struct SetupInfo
        {
            Format format = Format::Invalid;
            ImageBufferInfos imageBuffers;
        };

    public:
        Texture() = default;
        ~Texture() = default;

        bool Setup(const SetupInfo& info);
        bool Resize(const ImageBufferInfos& imageBuffers);
        void Clear(const Math::Vec4f& color);

        Image& GetImage(int index = 0)
        {
            return const_cast<Image&>(
                std::as_const(*this).GetImage(index));
        }

        const Image& GetImage(int index = 0) const
        {
            ASSERT(index >= 0 && index < m_images.size());
            return *m_images[index];
        }

        Format GetFormat() const
        {
            ASSERT(m_format != Format::Invalid);
            return m_format;
        }

        int GetWidth() const
        {
            ASSERT(!m_images.empty());
            return m_images[0]->GetWidth();
        }

        int GetHeight() const
        {
            ASSERT(!m_images.empty());
            return m_images[0]->GetHeight();
        }

    private:
        Format m_format = Format::Invalid;
        std::vector<std::unique_ptr<Image>> m_images;
    };
}
