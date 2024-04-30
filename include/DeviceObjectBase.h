#pragma once
#include <memory>

#include "Device.h"
#include "SelfRefBase.h"

template <class T>
class DeviceObjectBase: public SelfRefBase<T>
{
public:
	virtual ~DeviceObjectBase() {}

protected:
	virtual bool Init(const std::shared_ptr<Device>& pDevice, const std::shared_ptr<T>& pSelf)
	{
		if (!SelfRefBase<T>::Init(pSelf))
			return false;

		if (!pDevice.get())
			return false;

		m_pDevice = pDevice;
		return true;
	}

public:
	const std::shared_ptr<Device> GetDevice() const { return m_pDevice; };

protected:
	std::shared_ptr<Device> m_pDevice;
};
