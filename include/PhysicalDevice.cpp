#include <vector>
#include <limits> // Necessary for std::numeric_limits
#include <algorithm> // Necessary for std::clamp

#include "PhysicalDevice.h"
#include "SwapChain.h"
#include "VkUtility.h"

std::shared_ptr<PhysicalDevice> PhysicalDevice::Create(const std::shared_ptr<Instance>& pVulkanInstance, GLFWwindow* window)
{
    std::shared_ptr<PhysicalDevice> pPhysicalDevice = std::make_shared<PhysicalDevice>();
    if(pPhysicalDevice.get() && pPhysicalDevice->Init(pVulkanInstance, window))
    {
        return pPhysicalDevice;
    }

    return nullptr;
}

PhysicalDevice::SurfaceSupportDetails PhysicalDevice::QuerySurfaceSupport(VkPhysicalDevice device, VkSurfaceKHR surface)
{
    SurfaceSupportDetails details;

    //This function takes the specified VkPhysicalDevice and VkSurfaceKHR window surface into account when determining the supported capabilities.
    //All of the support querying functions have these two as first parameters because they are the core components of the swap chain.
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

    if (formatCount)
    {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
    }

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

    if (presentModeCount)
    {
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
    }

    return details;
}

bool PhysicalDevice::IsDeviceSuitable(VkPhysicalDevice device)
{
    vkGetPhysicalDeviceProperties(device, &m_physicalDeviceProperties);
    vkGetPhysicalDeviceFeatures(device, &m_physicalDeviceFeatures);
    vkGetPhysicalDeviceMemoryProperties(device, &m_physicalDeviceMemoryProperties);

    bool extensionsSupported = VkUtility::CheckDeviceExtensionsSupport(device, s_requiredDeviceExtensions);

    bool swapChainAdequate = false;
    if(extensionsSupported)
    {
        m_surfaceDetails = QuerySurfaceSupport(device, m_surface);
        swapChainAdequate = !m_surfaceDetails.formats.empty() && !m_surfaceDetails.presentModes.empty();
    }

    VkPhysicalDeviceFeatures supportedFeatures;
    vkGetPhysicalDeviceFeatures(device, &supportedFeatures);

    bool suitable = m_physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && extensionsSupported;// && swapChainAdequate;

    if (suitable)
    {
        std::cout << "physical device: " << m_physicalDeviceProperties.deviceName << std::endl;
    }
    return suitable;
}

bool PhysicalDevice::Init(const std::shared_ptr<Instance>& pVulkanInstance, GLFWwindow* window)
{
    m_pVulkanInstance = pVulkanInstance;
    const VkInstance vkInstance = pVulkanInstance->GetDeviceHandle();

    if (glfwCreateWindowSurface(pVulkanInstance->GetDeviceHandle(), window, nullptr, &m_surface) != VK_SUCCESS)
    {
        return false;
    }

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(vkInstance, &deviceCount, nullptr);
    assert(deviceCount != 0);
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(vkInstance, &deviceCount, devices.data());

    m_physicalDevice = VK_NULL_HANDLE;
    for(const auto& device: devices)
    {
        if(IsDeviceSuitable(device))
        {
            m_physicalDevice = device;
            break;
        }
    }

    if(m_physicalDevice == VK_NULL_HANDLE)
    {
        return false;
    }

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyCount, nullptr);
    if(queueFamilyCount == 0)
    {
        return false;
    }

    m_queueProperties.resize(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyCount, m_queueProperties.data());
    m_queueFamilyIndices[(uint32_t)QueueFamily::GRAPHICS] = -1;
    for (uint32_t i = 0; i < m_queueProperties.size(); i++)
    {
        if ((m_queueProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) &&
            (m_queueProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT) &&
            (m_queueProperties[i].queueFlags & VK_QUEUE_TRANSFER_BIT))
        {
            m_queueFamilyIndices[(uint32_t)QueueFamily::GRAPHICS] = i;
            break;
        }
    }

    assert(m_queueFamilyIndices[(uint32_t)QueueFamily::GRAPHICS] != -1);

    m_queueFamilyIndices[(uint32_t)QueueFamily::PRESENT] = -1;
    for (uint32_t i = 0; i < m_queueProperties.size(); i++)
    {
        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(m_physicalDevice, i, m_surface, &presentSupport);
        if (presentSupport)
        {
            m_queueFamilyIndices[(uint32_t)QueueFamily::PRESENT] = i;
            break;
        }
    }

    assert(m_queueFamilyIndices[(uint32_t)QueueFamily::PRESENT] != -1);

    m_queueFamilyIndices[(uint32_t)QueueFamily::COMPUTE] = -1;

    for (uint32_t i = 0; i < m_queueProperties.size(); i++)
    {
        if (!(m_queueProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) &&
            (m_queueProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT))
        {
            m_queueFamilyIndices[(uint32_t)QueueFamily::COMPUTE] = i;
            break;
        }
    }

    if (m_queueFamilyIndices[(uint32_t)QueueFamily::COMPUTE] == -1)
    {
        for (uint32_t i = 0; i < m_queueProperties.size(); i++)
        {
            if (m_queueProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT)
            {
                m_queueFamilyIndices[(uint32_t)QueueFamily::COMPUTE] = i;
                break;
            }
        }
    }

    assert(m_queueFamilyIndices[(uint32_t)QueueFamily::COMPUTE] != -1);

    m_queueFamilyIndices[(uint32_t)QueueFamily::TRANSFER] = -1;

    for (uint32_t i = 0; i < m_queueProperties.size(); i++)
    {
        if (!(m_queueProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) &&
            !(m_queueProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT) &&
            (m_queueProperties[i].queueFlags & VK_QUEUE_TRANSFER_BIT))
        {
            m_queueFamilyIndices[(uint32_t)QueueFamily::TRANSFER] = i;
            break;
        }
    }

    if (m_queueFamilyIndices[(uint32_t)QueueFamily::TRANSFER] == -1)
    {
        for (uint32_t i = 0; i < m_queueProperties.size(); i++)
        {
            if (m_queueProperties[i].queueFlags & VK_QUEUE_TRANSFER_BIT)
            {
                m_queueFamilyIndices[(uint32_t)QueueFamily::TRANSFER] = i;
                break;
            }
        }
    }

    assert(m_queueFamilyIndices[(uint32_t)QueueFamily::TRANSFER] != -1);

    // The VK_PRESENT_MODE_FIFO_KHR mode is guaranteed to be available
    m_presentMode = VK_PRESENT_MODE_FIFO_KHR;
    for (const auto& presentMode : m_surfaceDetails.presentModes)
    {
        if (presentMode == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            m_presentMode = presentMode;
        }
    }

    // extent may zero?
    //if (m_surfaceDetails.capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
    //{

    //}

    // hard code search swapchain color space and format
    m_surfaceFormat = m_surfaceDetails.formats[0];
    for (const auto& format : m_surfaceDetails.formats)
    {
        if (format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        {
            m_surfaceFormat = format;
        }
    }

    return true;
}

PhysicalDevice::~PhysicalDevice()
{
    vkDestroySurfaceKHR(m_pVulkanInstance->GetDeviceHandle(), m_surface, nullptr);
}
