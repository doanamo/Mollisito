#include "Shared.hpp"
#include "Formats.hpp"

Graphics::ImageInfo Graphics::GetImageInfo(Format format)
{
    ImageInfo info;

    switch(format)
    {
    case Format::R8G8B8A8_UINT:
        info.channelType = ChannelType::Uint8;
        info.channelSize = sizeof(uint8_t);
        info.channelCount = 4;
        info.padding = 0;
        break;

    case Format::R32_FLOAT:
        info.channelType = ChannelType::Float;
        info.channelSize = sizeof(float);
        info.channelCount = 1;
        info.padding = 0;
        break;

    default:
        ASSERT(false, "Invalid format");
    }

    return info;
}
