#pragma once
#include <vector>
#include <set>

namespace VkUtility
{
    bool CheckValidationLayerSupport(const std::vector<const char*> &);
    bool CheckDeviceExtensionsSupport(VkPhysicalDevice, const std::vector<const char*> &);
    std::vector<const char*> GetRequiredExtensions();
}