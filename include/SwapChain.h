#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <memory>

#include "Macros.h"
#include "DeviceObjectBase.h"



class SwapChain: public DeviceObjectBase
{  
public:
    static std::shared_ptr<SwapChain> Create(std::shared_ptr<Device> pDevice);

public:
    bool Init(std::shared_ptr<Device> pDevice);

    ~SwapChain();

private:
    VkSwapchainKHR m_swapChain;
    VkFormat m_swapChainImageFormat;
    VkExtent2D m_swapChainExtent;

    std::vector<VkImage> m_swapChainImages;
};