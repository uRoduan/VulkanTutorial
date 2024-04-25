#include "Application.h"

void Application::InitWindow()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // not create an OpenGL context
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE); // disable resize window

    m_window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan Tutorial", nullptr, nullptr);
    glfwSetWindowUserPointer(m_window, this);
    // glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

void Application::InitVulkanInstance()
{
    assert(VkUtility::CheckValidationLayerSupport(validationLayers));

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    auto requiredExtensions = VkUtility::GetRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
    createInfo.ppEnabledExtensionNames = requiredExtensions.data();
#ifdef _DEBUG
    createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
    createInfo.ppEnabledLayerNames = validationLayers.data();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};
    DebugMessengerExt::PopulateDebugMessagerCreateInfo(debugCreateInfo);
    createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
#else
    createInfo.enabledLayerCount = 0;
    createInfo.pNext = nullptr;
#endif

    m_pInstance = Instance::Create(createInfo);
    assert(m_pInstance != nullptr);

#ifdef _DEBUG
    m_debugMessenger = DebugMessengerExt::Create(debugCreateInfo, m_pInstance);
#else
    m_debugMessenger = nullptr;
#endif

    m_pInstance->LogVkSupportExtensions();
}

void Application::InitPhysicalDevice()
{
    m_pPhysicalDevice = PhysicalDevice::Create(m_pInstance);
}

void Application::MainLoop()
{
    while (!glfwWindowShouldClose(m_window)) {
        glfwPollEvents();
    }
}

void Application::CleanUp()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}