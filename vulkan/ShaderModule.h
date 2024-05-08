#pragma once
#include <string>
#include <fstream>

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
	static std::shared_ptr<ShaderModule> Create(const std::shared_ptr<Device>& pDevice, const std::wstring& path, const std::string& entryPoint, ShaderType type);

private:
	static std::vector<char> ReadFile(const std::wstring& path);

public:
	bool Init(const std::shared_ptr<Device>& pDevice, const std::shared_ptr<ShaderModule> pSelf, const std::wstring& path, const std::string& entryPoint, ShaderType type);
	VkShaderStageFlagBits GetShaderStage() const { return m_shaderStage; }
	std::string GetEntryPoint() const { return m_entryPoint; }

	~ShaderModule();

private:
	VkShaderModule m_shaderModule;
	ShaderType m_shaderType;
	VkShaderStageFlagBits m_shaderStage;
	std::string m_entryPoint;
};
