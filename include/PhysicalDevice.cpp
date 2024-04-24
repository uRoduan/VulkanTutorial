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

    

    return true;
}

bool PhysicalDevice::IsDeviceSuitable(VkPhysicalDevice device)
{
    vkGetPhysicalDeviceProperties(device, &m_physicalDeviceProperties);
    vkGetPhysicalDeviceFeatures(device, &m_physicalDeviceFeatures);
	vkGetPhysicalDeviceMemoryProperties(m_physicalDevice, &m_physicalDeviceMemoryProperties);

    bool extensionsSupported = VkUtility::CheckDeviceExtensionsSupport(device, s_requiredDeviceExtensions);

    bool swapChainAdequate = false;
    if(extensionsSupported)
    {
        SwapChainSupportDetails swapChainSupport = SwapChain::QuerySwapChainSupport(device);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }

    VkPhysicalDeviceFeatures supportedFeatures;
    vkGetPhysicalDeviceFeatures(device, &supportedFeatures);

    bool suitable = m_physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && extensionsSupported && swapChainAdequate;

    if(suitable)
    {
        std::cout << "physical device: " << m_physicalDeviceProperties.deviceName << std::endl;
    }
    return suitable;
}

void PhysicalDevice::FindQueueFamilies(VkPhysicalDevice device)
{
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for(const auto& queueFamily: queueFamilies)
    {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }

        i++;
    }
}