#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Macros.h"
#include "VkUtility.h"

namespace VkUtility
{
    bool CheckValidationLayerSupport(const std::vector<const char*> &validationLayers)
    {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
        for(const char* layerName : validationLayers)
        {
            bool layerFound = false;
            for(const auto& layerProperties: availableLayers)
            {
                if(strcmp(layerName, layerProperties.layerName) == 0)
                {
                    layerFound = true;
                    break;
                }
            }
            if(!layerFound)
            {
                return false;
            }
        }
        return true;
    }

    std::vector<const char*> GetRequiredExtensions()
    {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

#ifdef _DEBUG
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME); // for validation layer callback
#endif
        return extensions;
    }
}