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

        Texture() = default;
        ~Texture() = default;

        bool Setup(int width, int height, ChannelType channelType, int channelCount);

        void Clear(const Math::Vector4f& color);
        void SetPixel(int x, int y, const Math::Vector4f& color);
        Math::Vector4f GetPixel(int x, int y) const;

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

        int GetPitch() const
        {
            ASSERT(m_width);
            return m_width * GetChannelSize() * GetChannelCount();
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
            return const_cast<uint8_t*>(
                std::as_const(*this).GetPixelAddress(x, y));
        }

        const uint8_t* GetPixelAddress(int x, int y) const
        {
            ASSERT(x >= 0 && x < m_width);
            ASSERT(y >= 0 && y < m_height);
            return GetPixelAddress(y * m_width + x);
        }

        uint8_t* GetPixelAddress(size_t index)
        {
            return const_cast<uint8_t*>(
                std::as_const(*this).GetPixelAddress(index));
        }

        const uint8_t* GetPixelAddress(size_t index) const
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

        size_t GetDataSize() const
        {
            ASSERT(!m_data.empty());
            return m_data.size();
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
