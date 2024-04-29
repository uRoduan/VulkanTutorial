#include "DeviceObjectBase.h"

bool DeviceObjectBase::Init(const std::shared_ptr<Device>& pDevice)
{
	if (!pDevice.get())
		return false;

	m_pDevice = pDevice;
	return true;
}
