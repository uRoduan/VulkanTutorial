#pragma once
#include "DeviceObjectBase.h"

class Queue: public DeviceObjectBase<Queue>
{
public:
	static std::shared_ptr<Queue> Create(const std::shared_ptr<Device>& pDevice, PhysicalDevice::QueueFamily queueFamily);

public:
	bool Init(const std::shared_ptr<Device>& pDevice, PhysicalDevice::QueueFamily queueFamily, const std::shared_ptr<Queue>& pQueue);

private:
	PhysicalDevice::QueueFamily m_queueFamily;
	VkQueue m_queue;
};

