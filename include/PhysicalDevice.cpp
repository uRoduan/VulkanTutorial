#include <vector>

#include "PhysicalDevice.h"

std::shared_ptr<PhysicalDevice> PhysicalDevice::Create(const std::shared_ptr<Instance>& pVulkanInstance)
{
    std::shared_ptr<PhysicalDevice> pPhysicalDevice = std::make_shared<PhysicalDevice>();
    if(pPhysicalDevice.get() && pPhysicalDevice->Init(pVulkanInstance))
    {
        return pPhysicalDevice;
    }

    return nullptr;
}

void PhysicalDevice::Init(const std::shared_ptr<Instance>& pVulkanInstance)
{
    const VkInstance vkInstance = pVulkanInstance->GetDeviceHandle();
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(vkInstance, &deviceCount, nullptr);
    assert(deviceCount != 0);
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(vkInstance, &deviceCount, devices.data());

    for(const auto& device: devices)
    {

    }

}

bool PhysicalDevice::IsDeviceSuitable(VkPhysicalDevice device)
{
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    bool extensionsSupported = checkDeviceExtensionsSupport(device, s_requiredDeviceExtensions);
}