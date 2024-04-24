#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

#include "Instance.h"
#include "Macros.h"

const std::vector<const char*> s_requiredDeviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

class PhysicalDevice
{
public:
    enum class QueueFamilyIndices
    {
        GRAPHICS,
		COMPUTE,
		TRANSFER,
		COUNT
    };
public:
    static std::shared_ptr<PhysicalDevice> Create(const std::shared_ptr<Instance>& pVulkanInstance);

public:
    bool Init(const std::shared_ptr<Instance>& pVulkanInstance);
    ~PhysicalDevice();

private:
    bool IsDeviceSuitable(VkPhysicalDevice device);
    void FindQueueFamilies(VkPhysicalDevice device);

private:
    std::shared_ptr<Instance>			m_pVulkanInstance;
    VkPhysicalDevice                    m_physicalDevice;
    VkPhysicalDeviceProperties			m_physicalDeviceProperties;
    VkPhysicalDeviceFeatures			m_physicalDeviceFeatures;
    VkPhysicalDeviceMemoryProperties	m_physicalDeviceMemoryProperties;

	uint32_t							m_queueFamilyIndices[(uint32_t)QueueFamily::COUNT];

    //todo: determine depth format from physical device
};