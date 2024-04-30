#pragma once
#include <memory>

template <class T>
class SelfRefBase
{
public:
	std::shared_ptr<T> GetSelfSharedPtr() const
	{
		if (!m_pSelf.expired())
			return m_pSelf.lock();
		return nullptr;
	}

	virtual ~SelfRefBase() {}

protected:
	virtual bool Init(const std::shared_ptr<T>& pSelf)
	{
		m_pSelf = pSelf;
		return true;
	}

protected:
	std::weak_ptr<T> m_pSelf;
};