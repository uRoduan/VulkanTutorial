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

    VkInstance GetDeviceHandle() { return m_vkInstance; }
    const VkInstance GetDeviceHandle() const { return m_vkInstance; }

private:
    VkInstance m_vkInstance;
};