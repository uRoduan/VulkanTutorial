#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <memory>

#include "DeviceObjectBase.h"
#include "ImageView.h"

class SwapChain: public DeviceObjectBase<SwapChain>
{  
public:
    static std::shared_ptr<SwapChain> Create(std::shared_ptr<Device> pDevice);

public:
    bool Init(std::shared_ptr<Device> pDevice, std::shared_ptr<SwapChain> pSelf);

    ~SwapChain();

private:
    VkSwapchainKHR m_swapChain;
    VkFormat m_swapChainImageFormat;
    VkExtent2D m_swapChainExtent;

    std::vector<VkImage> m_swapChainImages;
    std::vector<std::shared_ptr<ImageView>> m_swapChainImageViews;
};