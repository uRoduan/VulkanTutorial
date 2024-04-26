#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <memory>

#include "Instance.h"
#include "PhysicalDevice.h"

class Device
{
public:
	static std::shared_ptr<Device> Create(const std::shared_ptr<Instance>& pInstance, const std::shared_ptr<PhysicalDevice>& pPhysicalDevice);

public:
	bool Init(const std::shared_ptr<Instance>& pInstance, const std::shared_ptr<PhysicalDevice>& pPhysicalDevice);

	~Device();

private:
	VkDevice						  m_device;
	std::shared_ptr<Instance>         m_pInstance;
	std::shared_ptr<PhysicalDevice>   m_pPhysicalDevice;
};