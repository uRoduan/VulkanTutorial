#pragma once
#include <vector>

namespace VkUtility
{
    bool CheckValidationLayerSupport(const std::vector<const char*> &);
    std::vector<const char*> GetRequiredExtensions();
}