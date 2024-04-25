#include <vector>

#include "PhysicalDevice.h"
#include "SwapChain.h"
#include "VkUtility.h"

std::shared_ptr<PhysicalDevice> PhysicalDevice::Create(const std::shared_ptr<Instance>& pVulkanInstance)
{
    std::shared_ptr<PhysicalDevice> pPhysicalDevice = std::make_shared<PhysicalDevice>();
    if(pPhysicalDevice.get() && pPhysicalDevice->Init(pVulkanInstance))
    {
        return pPhysicalDevice;
    }

    return nullptr;
}


bool PhysicalDevice::IsDeviceSuitable(VkPhysicalDevice device)
{
    vkGetPhysicalDeviceProperties(device, &m_physicalDeviceProperties);
    vkGetPhysicalDeviceFeatures(device, &m_physicalDeviceFeatures);
    vkGetPhysicalDeviceMemoryProperties(device, &m_physicalDeviceMemoryProperties);

    bool extensionsSupported = VkUtility::CheckDeviceExtensionsSupport(device, s_requiredDeviceExtensions);

    /*bool swapChainAdequate = false;
    if(extensionsSupported)
    {
        SwapChainSupportDetails swapChainSupport = SwapChain::QuerySwapChainSupport(device);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }*/

    VkPhysicalDeviceFeatures supportedFeatures;
    vkGetPhysicalDeviceFeatures(device, &supportedFeatures);

    bool suitable = m_physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && extensionsSupported;// && swapChainAdequate;

    if (suitable)
    {
        std::cout << "physical device: " << m_physicalDeviceProperties.deviceName << std::endl;
    }
    return suitable;
}

bool PhysicalDevice::Init(const std::shared_ptr<Instance>& pVulkanInstance)
{
    const VkInstance vkInstance = pVulkanInstance->GetDeviceHandle();
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
        }
    }

    assert(m_queueFamilyIndices[(uint32_t)QueueFamily::GRAPHICS] != -1);

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

    return true;
}
