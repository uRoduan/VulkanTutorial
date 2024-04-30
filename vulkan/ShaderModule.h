#pragma once
#include <string>

#include "DeviceObjectBase.h"

class ShaderModule: DeviceObjectBase<ShaderModule>
{
public:
	enum ShaderType
	{
		VERTEX,
		FRAGMENT,
		TYPECOUNT,
	};

public:
	static std::shared_ptr<ShaderModule> Create(const std::shared_ptr<Device>& pDevice, const std::wstring& path, ShaderType type);

public:
	bool Init(const std::shared_ptr<Device>& pDevice, const std::shared_ptr<ShaderModule> pSelf, const std::wstring& path, ShaderType type);
};
