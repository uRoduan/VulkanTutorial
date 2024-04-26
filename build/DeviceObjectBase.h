#pragma once
#include <memory>

#include "Device.h"

class DeviceObjectBase
{
public:
	virtual ~DeviceObjectBase() {}

protected:
	virtual bool Init(const std::shared_ptr<Device>& pDevice)
	{

	}

public:
	const std::shared_ptr<Device> GetDevice() const { return m_pDevice; };

protected:
	std::shared_ptr<Device> m_pDevice;
};

