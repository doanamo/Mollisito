#pragma once

namespace Graphics
{
    class Texture : private Common::NonCopyable
    {
    public:
        enum class ChannelType
        {
            Invalid,
            Uint8,
            Float,
        };

        struct BufferInfo
        {
            int width = 0;
            int height = 0;
            int pitch = 0;
            void* pixels = nullptr;
        };

        struct SetupInfo
        {
            ChannelType channelType = ChannelType::Invalid;
            int channelCount = 0;
            BufferInfo buffer;
        };

    public:
        Texture() = default;
        ~Texture() = default;

        bool Setup(const SetupInfo& info);
        bool Resize(const BufferInfo& info);

        void Clear(const Math::Vec4f& color);
        void SetPixel(int x, int y, const Math::Vec4f& color);
        Math::Vec4f GetPixel(int x, int y) const;

        ChannelType GetChannelType() const
        {
            ASSERT(m_channelType != ChannelType::Invalid);
            return m_channelType;
        }

        int GetChannelCount() const
        {
            ASSERT(m_channelCount > 0);
            return m_channelCount;
        }

        int GetChannelSize() const
        {
            ASSERT(m_channelSize > 0);
            return m_channelSize;
        }

        int GetWidth() const
        {
            ASSERT(m_width > 0);
            return m_width;
        }

        int GetHeight() const
        {
            ASSERT(m_height > 0);
            return m_height;
        }

        int GetPitch() const
        {
            ASSERT(m_pitch > 0);
            return m_pitch;
        }

        uint8_t* GetPixelAddress(int x, int y)
        {
            return const_cast<uint8_t*>(
                std::as_const(*this).GetPixelAddress(x, y));
        }

        const uint8_t* GetPixelAddress(int x, int y) const
        {
            ASSERT(x >= 0 && x < GetWidth());
            ASSERT(y >= 0 && y < GetHeight());
            return GetPixelAddress(y * GetWidth() + x);
        }

        uint8_t* GetPixelAddress(int index)
        {
            return const_cast<uint8_t*>(
                std::as_const(*this).GetPixelAddress(index));
        }

        const uint8_t* GetPixelAddress(int index) const
        {
            int pixelIndex = GetPixelSize() * index;
            ASSERT(pixelIndex >= 0 && pixelIndex < GetSize());
            return &GetPixels()[pixelIndex];
        }

        const uint8_t* GetPixels() const
        {
            ASSERT(m_pixelsPtr);
            return m_pixelsPtr;
        }

        int GetPixelSize() const
        {
            ASSERT(m_pixelSize > 0);
            return m_pixelSize;
        }

        int GetSize() const
        {
            return GetHeight() * GetPitch();
        }

    private:
        ChannelType m_channelType = ChannelType::Invalid;
        int m_channelCount = 0;
        int m_channelSize = 0;

        int m_width = 0;
        int m_height = 0;
        int m_pitch = 0;

        std::vector<uint8_t> m_pixels;
        uint8_t* m_pixelsPtr = nullptr;
        int m_pixelSize = 0;
    };
}
