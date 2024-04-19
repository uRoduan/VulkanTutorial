#include <vector>

#include "Instance.h"
#include "VkUtility.h"

static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) 
{

    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
    return VK_FALSE;
}

std::shared_ptr<Instance> Instance::Create(const VkInstanceCreateInfo& createInfo, bool enableValidationLayer)
{
    std::shared_ptr<Instance> pInstance = std::make_shared<Instance>();
    if (pInstance.get() && pInstance->Init(createInfo, enableValidationLayer))
    {
        return pInstance;
    }

    return nullptr;
}

bool Instance::Init(const VkInstanceCreateInfo& createInfo, bool enableValidationLayer)
{
    if(vkCreateInstance(&createInfo, nullptr, &m_vkInstance) != VK_SUCCESS)
    {
        return false;
    }

    if(enableValidationLayer)
    {
        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
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