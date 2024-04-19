#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <memory>

class Instance
{
public:
    static std::shared_ptr<Instance> Create(const VkInstanceCreateInfo&, bool);

public:
    bool Init(const VkInstanceCreateInfo&, bool);
    void LogVkSupportExtensions();

private:
    VkInstance m_vkInstance;
};