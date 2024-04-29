#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <memory>

#include "Instance.h"
#include "PhysicalDevice.h"

const std::vector<const char*> s_requiredDeviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

class Device
{
public:
	static std::shared_ptr<Device> Create(const std::shared_ptr<Instance>& pInstance, const std::shared_ptr<PhysicalDevice>& pPhysicalDevice);

public:
	VkDevice GetDeviceHandle() const { return m_device; }
	std::shared_ptr<Instance> GetInstance() const { return m_pInstance; }
	std::shared_ptr<PhysicalDevice> GetPhysicalDevice() const { return m_pPhysicalDevice; }

	bool Init(const std::shared_ptr<Instance>& pInstance, const std::shared_ptr<PhysicalDevice>& pPhysicalDevice);

	~Device();

private:
	VkDevice						  m_device;
	std::shared_ptr<Instance>         m_pInstance;
	std::shared_ptr<PhysicalDevice>   m_pPhysicalDevice;
};