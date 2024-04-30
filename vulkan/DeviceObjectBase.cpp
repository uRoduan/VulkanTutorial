//#include "DeviceObjectBase.h"
//
//template<class T>
//bool DeviceObjectBase<T>::Init(const std::shared_ptr<Device>& pDevice, const std::shared_ptr<T>& pSelf)
//{
//	if (!SelfRefBase<T>::Init(pSelf))
//		return false;
//
//	if (!pDevice.get())
//		return false;
//
//	m_pDevice = pDevice;
//	return true;
//}