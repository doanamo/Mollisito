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

    void Texture::Clear(const Math::Color4b& color)
    {
        for(int y = 0; y < m_height; ++y)
        {
            for(int x = 0; x < m_width; ++x)
            {
                DrawPixel(x, y, color);
            }
        }
    }

    void Texture::Clear(const Math::Color4f& color)
    {
        for(int y = 0; y < m_height; ++y)
        {
            for(int x = 0; x < m_width; ++x)
            {
                DrawPixel(x, y, color);
            }
        }
    }

    void Texture::DrawPixel(int x, int y, const Math::Color4b& color)
    {
        if(m_channelType == ChannelType::Uint8)
        {
            uint8_t* pixel = GetPixelAddress(x, y);
            for(int i = 0; i < m_channelCount; ++i)
            {
                pixel[i] = color.array[i];
            }
        }
        else if(m_channelType == ChannelType::Float)
        {
            DrawPixel(x, y, Math::Color4f(color));
        }
        else
        {
            ASSERT(false, "Unimplemented");
        }
    }

    void Texture::DrawPixel(int x, int y, const Math::Color4f& color)
    {
        if(m_channelType == ChannelType::Float)
        {
            auto pixel = (float*)GetPixelAddress(x, y);
            for(int i = 0; i < m_channelCount; ++i)
            {
                pixel[i] = color.array[i];
            }
        }
        else if(m_channelType == ChannelType::Uint8)
        {
            DrawPixel(x, y, Math::Color4b(color));
        }
        else
        {
            ASSERT(false, "Unimplemented");
        }
    }
}
