#include "Shared.hpp"
#include "Texture.hpp"

bool Graphics::Texture::Setup(const SetupInfo& info)
{
    if(info.channelCount <= 0 || info.channelCount > 4)
    {
        LOG_ERROR("Failed to setup texture due to invalid channel count");
        return false;
    }

    int channelSize = 0;
    switch(info.channelType)
    {
    case ChannelType::Uint8:
        channelSize = sizeof(uint8_t);
        break;

    case ChannelType::Float:
        channelSize = sizeof(float);
        break;

    default:
        LOG_ERROR("Failed to setup texture due to invalid channel type");
        return false;
    }

    m_channelType = info.channelType;
    m_channelCount = info.channelCount;
    m_channelSize = channelSize;

    if(!Resize(info.buffer))
    {
        LOG_ERROR("Failed to setup texture due to invalid dimensions");
        return false;
    }

    return true;
}

bool Graphics::Texture::Resize(const BufferInfo& info)
{
    if(info.width < 0 || info.height < 0)
    {
        return false;
    }

    m_width = info.width;
    m_height = info.height;

    if(info.pixels)
    {
        m_pitch = info.pitch;
        m_pixelsPtr = (uint8_t*)info.pixels;
        m_pixels.clear();
    }
    else
    {
        m_pitch = m_width * m_channelSize * m_channelCount;
        m_pixels.resize(m_height * m_pitch);
        m_pixelsPtr = m_pixels.data();
    }

    m_pixelSize = m_pitch / m_width;
    if(m_pitch % m_width != 0)
    {
        LOG_ERROR("Failed to resize texture due to invalid pitch size");
        return false;
    }

    return true;
}

void Graphics::Texture::Clear(const Math::Vec4f& color)
{
    if(m_channelType == ChannelType::Uint8 && m_channelCount == 4)
    {
        if(color.IsUniform())
        {
            auto pattern = (uint8_t)(color.r * 255.0f);
            memset(m_pixelsPtr, pattern, m_height * m_pitch);
        }
        else
        {
            uint32_t value = (uint8_t)(color.r * 255.0f);
            value |= (uint8_t)(color.g * 255.0f) << 8;
            value |= (uint8_t)(color.b * 255.0f) << 16;
            value |= (uint8_t)(color.a * 255.0f) << 24;

            for(int i = 0; i < m_width * m_height; ++i)
            {
                (uint32_t&)m_pixelsPtr[i * m_pixelSize] = value; 
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

void Graphics::Texture::SetPixel(int x, int y, const Math::Vec4f& color)
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

Math::Vec4f Graphics::Texture::GetPixel(int x, int y) const
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
