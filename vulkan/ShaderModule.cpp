#include "ShaderModule.h"

std::shared_ptr<ShaderModule> ShaderModule::Create(const std::shared_ptr<Device>& pDevice, const std::wstring& path, const std::string& entryPoint, ShaderType type)
{
    std::shared_ptr<ShaderModule> pShaderModule = std::make_shared<ShaderModule>();
    if (pShaderModule.get() && pShaderModule->Init(pDevice, pShaderModule, path, entryPoint, type))
    {
        return pShaderModule;
    }

    return nullptr;
}

std::vector<char> ShaderModule::ReadFile(const std::wstring& path)
{
    std::ifstream file(path, std::ios::ate | std::ios::binary); // ate: start reading at the end of the file; binary: read the file as binary file

    if (!file.is_open())
    {
        throw std::runtime_error("failed to open file!");
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}

bool ShaderModule::Init(const std::shared_ptr<Device>& pDevice, const std::shared_ptr<ShaderModule> pSelf, const std::wstring& path, const std::string& entryPoint, ShaderType type)
{
    std::vector<char> shaderCode = ReadFile(path);
    m_entryPoint = entryPoint;
    m_shaderType = type;
    switch (m_shaderType)
    {
        case VERTEX: 
            m_shaderStage = VK_SHADER_STAGE_VERTEX_BIT;
            break;
        case FRAGMENT: 
            m_shaderStage = VK_SHADER_STAGE_FRAGMENT_BIT;
            break;
        default: 
            assert(false);
    }

    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = shaderCode.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(shaderCode.data());

    if (vkCreateShaderModule(pDevice->GetDeviceHandle(), &createInfo, nullptr, &m_shaderModule) != VK_SUCCESS) 
    {
        return false;
    }

    return true;
}

ShaderModule::~ShaderModule()
{
    vkDestroyShaderModule(m_pDevice->GetDeviceHandle(), m_shaderModule, nullptr);
}
