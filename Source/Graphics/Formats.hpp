#pragma once

namespace Graphics
{
    enum class Format
    {
        Invalid,
        R8G8B8A8_UINT,
        R32_FLOAT,
    };

    enum class ChannelType
    {
        Invalid,
        Uint8,
        Float,
    };

    struct ImageInfo
    {
        ChannelType channelType = ChannelType::Invalid;
        int channelSize = 0;
        int channelCount = 0;
        int padding = 0;
    };

    ImageInfo GetImageInfo(Format format);
}
