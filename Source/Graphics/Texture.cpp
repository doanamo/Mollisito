#include "Shared.hpp"
#include "Texture.hpp"

namespace Graphics
{
    bool Texture::Setup(int width, int height, ChannelType channelType, int channelCount)
    {
        if(width < 0 || height < 0)
        {
            return false;
        }

        if(channelType == ChannelType::Invalid)
        {
            return false;
        }

        if(channelCount < 0 || channelCount > 8)
        {
            return false;
        }

        int channelSize = 0;
        switch(channelType)
        {
        case ChannelType::Uint8:
            channelSize = sizeof(uint8_t);
            break;

        case ChannelType::Float:
            channelSize = sizeof(float);
            break;
        }

        m_width = width;
        m_height = height;
        m_channelType = channelType;
        m_channelSize = channelSize;
        m_channelCount = channelCount;

        m_data.resize(m_width * m_height * m_channelSize * m_channelCount);

        return true;
    }

    void Texture::Clear(const Math::Vector4f& color)
    {
        if(m_channelType == ChannelType::Uint8 && m_channelCount == 4)
        {
            if(color.IsUniform())
            {
                uint8_t pattern = (uint8_t)(color.r * 255.0f + 0.5f);
                memset(m_data.data(), pattern, m_data.size());
            }
            else
            {
                uint32_t value = (uint8_t)(color.r * 255.0f);
                value |= (uint8_t)(color.g * 255.0f) << 8;
                value |= (uint8_t)(color.b * 255.0f) << 16;
                value |= (uint8_t)(color.a * 255.0f) << 24;

                for(int i = 0; i < m_width * m_height; ++i)
                {
                    (uint32_t&)m_data[i * 4] = value;
                }
            }
        }
        else
        {
            for(int y = 0; y < m_height; ++y)
            {
                for(int x = 0; x < m_width; ++x)
                {
                    SetPixel(x, y, color);
                }
            }
        }
    }

    void Texture::SetPixel(int x, int y, const Math::Vector4f& color)
    {
        if(m_channelType == ChannelType::Uint8)
        {
            uint8_t* pixel = GetPixelAddress(x, y);
            for(int i = 0; i < m_channelCount; ++i)
            {
                pixel[i] = (uint8_t)(color.array[i] * 255.0f + 0.5f);
            }
        }
        else if(m_channelType == ChannelType::Float)
        {
            float* pixel = (float*)GetPixelAddress(x, y);
            for(int i = 0; i < m_channelCount; ++i)
            {
                pixel[i] = color.array[i];
            }
        }
    }
}
