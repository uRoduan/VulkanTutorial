#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <memory>

#include "Instance.h"

class PhysicalDevice
{
public:
    static const std::vector<const char*> s_requiredDeviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
    
public:
    static std::shared_ptr<PhysicalDevice> Create(const std::shared_ptr<Instance>& pVulkanInstance);

public:
    void Init(const std::shared_ptr<Instance>& pVulkanInstance);

private:
    bool IsDeviceSuitable(VkPhysicalDevice device);

private:
    VkPhysicalDevice m_physicalDevice;
}