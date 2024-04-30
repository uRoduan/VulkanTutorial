#include "Queue.h"

std::shared_ptr<Queue> Queue::Create(const std::shared_ptr<Device>& pDevice, PhysicalDevice::QueueFamily queueFamily)
{
	std::shared_ptr<Queue> pQueue = std::make_shared<Queue>();
	if (pQueue.get() && pQueue->Init(pDevice, queueFamily, pQueue))
	{
		return pQueue;
	}

	return nullptr;
}

bool Queue::Init(const std::shared_ptr<Device>& pDevice, PhysicalDevice::QueueFamily queueFamily, const std::shared_ptr<Queue>& pQueue)
{
	if (!DeviceObjectBase::Init(pDevice, pQueue))
	{
		return false;
	}

	vkGetDeviceQueue(pDevice->GetDeviceHandle(), pDevice->GetPhysicalDevice()->GetQueueFamilyIndex(queueFamily), 0, &m_queue);
	m_queueFamily = queueFamily;

	return true;
}
