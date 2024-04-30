#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <memory>

#include "Instance.h"

class DebugMessengerExt
{
public:
    static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData);
    static void PopulateDebugMessagerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    static std::shared_ptr<DebugMessengerExt> Create(const VkDebugUtilsMessengerCreateInfoEXT&, const std::shared_ptr<Instance>&);

public:
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
        const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, 
        const VkAllocationCallbacks* pAllocator);
    bool Init(const VkDebugUtilsMessengerCreateInfoEXT&, const std::shared_ptr<Instance>&);

    ~DebugMessengerExt();

private:
    std::shared_ptr<Instance>			m_pVulkanInstance;
    VkDebugUtilsMessengerEXT            m_debugMessenger;
};