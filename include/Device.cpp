#include <set>
#include <array>
#include <vector>
#include "Device.h"

std::shared_ptr<Device> Device::Create(const std::shared_ptr<Instance>& pInstance, const std::shared_ptr<PhysicalDevice>& pPhysicalDevice)
{
	std::shared_ptr<Device> device = std::make_shared<Device>();
	if (device.get() && device->Init(pInstance, pPhysicalDevice))
	{
		return device;
	}

	return nullptr;
}

bool Device::Init(const std::shared_ptr<Instance>& pInstance, const std::shared_ptr<PhysicalDevice>& pPhysicalDevice)
{
	m_pInstance = pInstance;
	m_pPhysicalDevice = pPhysicalDevice;

	std::set<uint32_t> queueIndexSet;
	queueIndexSet.insert(m_pPhysicalDevice->GetQueueFamilyIndex(PhysicalDevice::QueueFamily::GRAPHICS));
	queueIndexSet.insert(m_pPhysicalDevice->GetQueueFamilyIndex(PhysicalDevice::QueueFamily::COMPUTE));
	queueIndexSet.insert(m_pPhysicalDevice->GetQueueFamilyIndex(PhysicalDevice::QueueFamily::TRANSFER));

	std::array<float, 1> queueProperties = { 1.0f };
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	for (auto queueIndex : queueIndexSet)
	{
		VkDeviceQueueCreateInfo info = {};
		info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		info.queueFamilyIndex = queueIndex;
		info.queueCount = (uint32_t)queueProperties.size();
		info.pQueuePriorities = queueProperties.data();
		queueCreateInfos.push_back(info);
	}

	VkPhysicalDeviceFeatures deviceFeatures{};
	deviceFeatures.samplerAnisotropy = true;

	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = queueCreateInfos.data();
	createInfo.queueCreateInfoCount = (uint32_t)queueCreateInfos.size();
	// todo: set device extensions here
	/*createInfo.ppEnabledExtensionNames = s_requiredDeviceExtensions.data();
	createInfo.enabledExtensionCount = (uint32_t)s_requiredDeviceExtensions.size();*/
	createInfo.pEnabledFeatures = &deviceFeatures;

	if (vkCreateDevice(m_pPhysicalDevice->GetDeviceHandle(), &createInfo, nullptr, &m_device) != VK_SUCCESS)
	{
		return false;
	}
	
	return true;
}

Device::~Device()
{
	vkDestroyDevice(m_device, nullptr);
}
