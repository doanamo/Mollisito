#include "Shared.hpp"
#include "Texture.hpp"

bool Graphics::Texture::Setup(const SetupInfo& info)
{
    ImageInfo imageInfo = GetImageInfo(info.format);
    if(imageInfo.channelType == ChannelType::Invalid)
    {
        LOG_ERROR("Failed to setup texture due to invalid format");
        return false;
    }

    m_format = info.format;

    for(const Image::BufferInfo& bufferInfo : info.imageBuffers)
    {
        Image::SetupInfo imageSetup;
        imageSetup.image = imageInfo;
        imageSetup.buffer = bufferInfo;

        auto image = std::make_unique<Image>();
        if(!image->Setup(imageSetup))
        {
            LOG_ERROR("Failed to setup texture due to image setup failure");
            return false;
        }

        m_images.push_back(std::move(image));
    }

    return true;
}

bool Graphics::Texture::Resize(const ImageBufferInfos& imageBuffers)
{
    if(imageBuffers.size() != m_images.size())
    {
        LOG_ERROR("Failed to resize texture due to invalid image count");
        return false;
    }

    for(int i = 0; i < m_images.size(); ++i)
    {
        auto& image = m_images[i];
        if(!image->Resize(imageBuffers[i]))
        {
            LOG_ERROR("Failed to resize texture image");
            return false;
        }
    }

    return true;
}

void Graphics::Texture::Clear(const Math::Vec4f& color)
{
    for(auto& image : m_images)
    {
        image->Clear(color);
    }
}
