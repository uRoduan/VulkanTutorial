#include "Queue.h"

std::shared_ptr<Queue> Queue::Create(const std::shared_ptr<Device>& pDevice, PhysicalDevice::QueueFamily queueFamily)
{
	std::shared_ptr<Queue> queue = std::make_shared<Queue>();
	if (queue.get() && queue->Init(pDevice, queueFamily))
	{
		return queue;
	}

	return nullptr;
}

bool Queue::Init(const std::shared_ptr<Device>& pDevice, PhysicalDevice::QueueFamily queueFamily)
{
	if (!DeviceObjectBase::Init(pDevice))
	{
		return false;
	}

	vkGetDeviceQueue(pDevice->GetDeviceHandle(), pDevice->GetPhysicalDevice()->GetQueueFamilyIndex(queueFamily), 0, &m_queue);
	m_queueFamily = queueFamily;

	return true;
}
