#include "ImageView.h"

std::shared_ptr<ImageView> ImageView::Create(const std::shared_ptr<Device>& pDevice, const VkImageViewCreateInfo& createInfo)
{
    std::shared_ptr<ImageView> pImageView = std::make_shared<ImageView>();
    if (pImageView.get() && pImageView->Init(pDevice, pImageView, createInfo))
    {
        return pImageView;
    }

    return nullptr;
}

bool ImageView::Init(const std::shared_ptr<Device>& pDevice, const std::shared_ptr<ImageView>& pSelf, const VkImageViewCreateInfo& createInfo)
{
    if (!DeviceObjectBase::Init(pDevice, pSelf))
    {
        return false;
    }

    if (vkCreateImageView(m_pDevice->GetDeviceHandle(), &createInfo, nullptr, &m_imageView) != VK_SUCCESS)
    {
        return false;
    }

    return true;
}

ImageView::~ImageView()
{
    if (m_imageView)
    {
        vkDestroyImageView(m_pDevice->GetDeviceHandle(), m_imageView, nullptr);
    }
}