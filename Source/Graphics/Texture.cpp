#include "Shared.hpp"
#include "Texture.hpp"

namespace Graphics
{
    bool Texture::Setup(int width, int height, ChannelType channelType, int channelCount)
    {
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

        m_channelType = channelType;
        m_channelSize = channelSize;
        m_channelCount = channelCount;

        if(!Resize(width, height))
        {
            return false;
        }

        return true;
    }

    bool Texture::Resize(int width, int height)
    {
        if(width < 0 || height < 0)
        {
            return false;
        }

        m_width = width;
        m_height = height;

        m_data.resize(m_width * m_height * m_channelSize * m_channelCount);

        return true;
    }

    void Texture::Clear(const Math::Vec4f& color)
    {
        if(m_channelType == ChannelType::Uint8 && m_channelCount == 4)
        {
            if(color.IsUniform())
            {
                auto pattern = (uint8_t)(color.r * 255.0f);
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

    void Texture::SetPixel(int x, int y, const Math::Vec4f& color)
    {
        if(m_channelType == ChannelType::Uint8)
        {
            uint8_t* pixel = GetPixelAddress(x, y);
            for(int i = 0; i < m_channelCount; ++i)
            {
                pixel[i] = (uint8_t)(color.array[i] * 255.0f);
            }
        }
        else if(m_channelType == ChannelType::Float)
        {
            auto* pixel = (float*)GetPixelAddress(x, y);
            for(int i = 0; i < m_channelCount; ++i)
            {
                pixel[i] = color.array[i];
            }
        }
    }

    Math::Vec4f Texture::GetPixel(int x, int y) const
    {
        Math::Vec4f result = Color::Black;
        if(m_channelType == ChannelType::Uint8)
        {
            const uint8_t* pixel = GetPixelAddress(x, y);
            for(int i = 0; i < m_channelCount; ++i)
            {
                result.array[i] = (uint8_t)(pixel[i] * (1.0f / 255.0f));
            }
        }
        else if(m_channelType == ChannelType::Float)
        {
            auto* pixel = (const float*)GetPixelAddress(x, y);
            for(int i = 0; i < m_channelCount; ++i)
            {
                result.array[i] = pixel[i];
            }
        }

        return result;
    }
}
