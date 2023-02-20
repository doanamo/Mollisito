#pragma once

#include "Math/Color.hpp"

namespace Graphics
{
    class Texture
    {
    public:
        enum class ChannelType
        {
            Invalid,
            Uint8,
            Float,
        };

        Texture() = default;
        ~Texture() = default;

        bool Setup(int width, int height, ChannelType channelType, int channelCount);

        void Clear(const Math::Color& color);
        void DrawPixel(int x, int y, const Math::Color& color);

        int GetWidth() const
        {
            ASSERT(m_width);
            return m_width;
        }

        int GetHeight() const
        {
            ASSERT(m_height);
            return m_height;
        }

        ChannelType GetChannelType() const
        {
            ASSERT(m_channelType != ChannelType::Invalid);
            return m_channelType;
        }

        int GetChannelSize() const
        {
            ASSERT(m_channelSize);
            return m_channelSize;
        }

        int GetChannelCount() const
        {
            ASSERT(m_channelCount);
            return m_channelCount;
        }

        uint8_t* GetPixelAddress(int x, int y)
        {
            ASSERT(x >= 0 && x < m_width);
            ASSERT(y >= 0 && y < m_height);
            return GetPixelAddress(y * m_width + x);
        }

        uint8_t* GetPixelAddress(size_t index)
        {
            size_t pixelIndex = GetChannelSize() * m_channelCount * index;
            ASSERT(pixelIndex >= 0 && pixelIndex < m_data.size());
            return &m_data[pixelIndex];
        }

        const uint8_t* GetData() const
        {
            ASSERT(!m_data.empty());
            return m_data.data();
        }

    private:
        int m_width = 0;
        int m_height = 0;

        ChannelType m_channelType = ChannelType::Invalid;
        int m_channelSize = 0;
        int m_channelCount = 0;

        std::vector<uint8_t> m_data;
    };
}
