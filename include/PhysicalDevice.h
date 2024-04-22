#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <memory>

class PhysicalDevice
{
public:
    static std::shared_ptr<PhysicalDevice> Create()

private:
    VkPhysicalDevice m_physicalDevice;
}