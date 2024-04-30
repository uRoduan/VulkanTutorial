#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

#include "Instance.h"
#include "Macros.h"

class PhysicalDevice
{
public:
    enum class QueueFamily
    {
        GRAPHICS,
        PRESENT,
		COMPUTE,
		TRANSFER,
		COUNT
    };

    struct SurfaceSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };
public:
    static std::shared_ptr<PhysicalDevice> Create(const std::shared_ptr<Instance>& pVulkanInstance, GLFWwindow* window);

public:
    bool Init(const std::shared_ptr<Instance>& pVulkanInstance, GLFWwindow* window);
    uint32_t GetQueueFamilyIndex(QueueFamily queueFamily) const { return m_queueFamilyIndices[(uint32_t)queueFamily]; }
    VkPhysicalDevice GetDeviceHandle() const { return m_physicalDevice; }
    VkSurfaceKHR GetSurfaceHandle() const { return m_surface; }
    VkPresentModeKHR GetPresentMode() const { return m_presentMode; }
    VkSurfaceCapabilitiesKHR GetSurfaceCapabilities() const { return m_surfaceDetails.capabilities; }
    VkSurfaceFormatKHR GetSurfaceFormat()  const { return m_surfaceFormat; }

     ~PhysicalDevice();

private:
    bool IsDeviceSuitable(VkPhysicalDevice device);
    SurfaceSupportDetails QuerySurfaceSupport(VkPhysicalDevice, VkSurfaceKHR);

private:
    std::shared_ptr<Instance>			    m_pVulkanInstance;

    std::vector<VkQueueFamilyProperties>    m_queueProperties;
    VkPhysicalDevice                        m_physicalDevice;
    VkPhysicalDeviceProperties			    m_physicalDeviceProperties;
    VkPhysicalDeviceFeatures			    m_physicalDeviceFeatures;
    VkPhysicalDeviceMemoryProperties	    m_physicalDeviceMemoryProperties;

    VkSurfaceKHR                            m_surface;
    SurfaceSupportDetails                   m_surfaceDetails;
    VkPresentModeKHR                        m_presentMode;
    VkSurfaceFormatKHR                      m_surfaceFormat;

	uint32_t							    m_queueFamilyIndices[(uint32_t)QueueFamily::COUNT];

    //todo: determine depth format from physical device
};