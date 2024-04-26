#include "Queue.h"

std::shared_ptr<Queue> Queue::Create(const std::shared_ptr<Device>& pDevice, PhysicalDevice::QueueFamily queueFamily)
{
	return std::shared_ptr<Queue>();
}

bool Queue::Init(const std::shared_ptr<Device>& pDevice, PhysicalDevice::QueueFamily queueFamily)
{
	return false;
}
