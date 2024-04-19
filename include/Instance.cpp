#include <vector>

#include "Instance.h"
#include "Macros.h"
#include "VkUtility.h"

static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) 
{

    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
    return VK_FALSE;
}

std::shared_ptr<Instance> Instance::Create(const VkInstanceCreateInfo& createInfo)
{
    std::shared_ptr<Instance> pInstance = std::make_shared<Instance>();
    if (pInstance.get() && pInstance->Init(createInfo))
    {
        return pInstance;
    }

    return nullptr;
}

bool Instance::Init(const VkInstanceCreateInfo& createInfo)
{
    if(vkCreateInstance(&createInfo, nullptr, &m_vkInstance) != VK_SUCCESS)
    {
        return false;
    }

    return true;
}

void Instance::LogVkSupportExtensions()
{
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    std::cout << "available extensions:\n";

    for (const auto& extension: extensions) {
        std::cout << "\t" << extension.extensionName << "\n";
    }
}

Instance::~Instance()
{
    if(m_vkInstance)
    {
        vkDestroyInstance(m_vkInstance, nullptr);
    }
}