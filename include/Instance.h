#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <memory>

#include "Macros.h"

class Instance
{
public:
    static std::shared_ptr<Instance> Create(const VkInstanceCreateInfo&);

public:
    bool Init(const VkInstanceCreateInfo&);
    void LogVkSupportExtensions();

    ~Instance();

private:
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                            const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

private:
    VkInstance m_vkInstance;

#ifdef _DEBUG
    VkDebugUtilsMessengerEXT m_debugMessenger;
#endif
};