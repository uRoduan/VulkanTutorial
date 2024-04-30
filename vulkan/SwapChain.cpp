#include "SwapChain.h"

std::shared_ptr<SwapChain> SwapChain::Create(std::shared_ptr <Device> pDevice)
{
    std::shared_ptr<SwapChain> pSwapChain = std::make_shared<SwapChain>();
    if (pSwapChain.get() && pSwapChain->Init(pDevice, pSwapChain))
    {
        return pSwapChain;
    }

    return nullptr;
}

bool SwapChain::Init(std::shared_ptr<Device> pDevice, std::shared_ptr<SwapChain> pSelf)
{
    if (!DeviceObjectBase::Init(pDevice, pSelf))
    {
        return false;
    }

    std::shared_ptr<PhysicalDevice> pPhysicalDevice = pDevice->GetPhysicalDevice();
    const VkSurfaceCapabilitiesKHR& capabilities = pPhysicalDevice->GetSurfaceCapabilities();
    const VkSurfaceFormatKHR& surfaceFormat = pPhysicalDevice->GetSurfaceFormat();
    m_swapChainImageFormat = surfaceFormat.format;
    m_swapChainExtent = capabilities.currentExtent;

    uint32_t swapChainImageCount = capabilities.minImageCount + 1;
    if (capabilities.maxImageCount > 0)
    {
        swapChainImageCount = std::min(swapChainImageCount, capabilities.maxImageCount);
    }
    uint32_t queueFamilyIndices[] =
    {
        pPhysicalDevice->GetQueueFamilyIndex(PhysicalDevice::QueueFamily::GRAPHICS),
        pPhysicalDevice->GetQueueFamilyIndex(PhysicalDevice::QueueFamily::PRESENT)
    };

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = pPhysicalDevice->GetSurfaceHandle();
    createInfo.minImageCount = swapChainImageCount;
    createInfo.imageFormat = m_swapChainImageFormat;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = m_swapChainExtent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    if (queueFamilyIndices[0] != queueFamilyIndices[1]) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    }
    else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0; // Optional
        createInfo.pQueueFamilyIndices = nullptr; // Optional
    }
    createInfo.preTransform = capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = pPhysicalDevice->GetPresentMode();
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    if (vkCreateSwapchainKHR(pDevice->GetDeviceHandle(), &createInfo, nullptr, &m_swapChain) != VK_SUCCESS) {
        return false;
    }

    vkGetSwapchainImagesKHR(pDevice->GetDeviceHandle(), m_swapChain, &swapChainImageCount, nullptr);
    m_swapChainImages.resize(swapChainImageCount);
    vkGetSwapchainImagesKHR(pDevice->GetDeviceHandle(), m_swapChain, &swapChainImageCount, m_swapChainImages.data());

    m_swapChainImageViews.resize(swapChainImageCount);
    for (size_t i = 0; i < swapChainImageCount; i++)
    {
        VkImageViewCreateInfo imageViewCreateInfo{};
        imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        imageViewCreateInfo.image = m_swapChainImages[i];
        imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        imageViewCreateInfo.format = m_swapChainImageFormat;
        imageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
        imageViewCreateInfo.subresourceRange.levelCount = 1;
        imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
        imageViewCreateInfo.subresourceRange.layerCount = 1;

        m_swapChainImageViews[i] = ImageView::Create(pDevice, imageViewCreateInfo);
        assert(m_swapChainImageViews[i] != nullptr);
    }

    return true;
}

SwapChain::~SwapChain()
{
    if (m_swapChain)
    {
        vkDestroySwapchainKHR(m_pDevice->GetDeviceHandle(), m_swapChain, nullptr);
    }
}
