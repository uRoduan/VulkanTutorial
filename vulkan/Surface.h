#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <memory>

#include "Instance.h"

class Surface
{
public:
	static std::shared_ptr<Surface> Create();
public:
	bool Init();

private:
	std::shared_ptr<Instance> m_pInstance;
	VkSurfaceKHR m_surface;
};

