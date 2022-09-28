#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <cstring>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

class HelloTriangleApplication
{
public:

    void run()
    {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    void initWindow()
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // not create an OpenGL context
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // disable resize window

        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan Tutorial", nullptr, nullptr);
    }

    void initVulkan()
    {
        createInstance();
    }

    void createInstance()
    {
        if(enableValidationLayers && !checkValidationLayerSupport())
        {
            throw std::runtime_error("validation layers requested, but not available!");
        }

        VkApplicationInfo appInfo{}; // optional
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO; // This is also one of the many structs with a pNext member that can point to extension information in the future.
        // appInfo.pNext = nullptr; default value is nullptr
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{}; // tells the vulkan driver which global extensions and validation layers we want to use
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        if(enableValidationLayers)
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        }
        else
        {
            createInfo.enabledLayerCount = 0;
        }

        std::vector<const char*> requiredExtensions;

        for(uint32_t i = 0; i < glfwExtensionCount; i++)
        {
            requiredExtensions.emplace_back(glfwExtensions[i]);
        }

#ifdef MAC_OS
         requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
         createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#endif

        createInfo.enabledExtensionCount = (uint32_t) requiredExtensions.size();
        createInfo.ppEnabledExtensionNames = requiredExtensions.data();

        //get vk supported extensions
//        uint32_t extensionCount = 0;
//        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
//        std::vector<VkExtensionProperties> extensions(extensionCount);
//        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
//
//        std::cout << "available extensions:\n";
//
//        for (const auto& extension: extensions) {
//            std::cout << "\t" << extension.extensionName << "\n";
//        }

        if(vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create instance!");
        }
    }

    void mainLoop()
    {
        while(!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
        }
    }

    void cleanup()
    {
        vkDestroyInstance(instance, nullptr);

        glfwDestroyWindow(window);

        glfwTerminate();
    }

    bool checkValidationLayerSupport()
    {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for(const char* layerName : validationLayers)
        {
            bool layerFound = false;

            for(const auto& layerProperties: availableLayers)
            {
                if(strcmp(layerName, layerProperties.layerName) == 0)
                {
                    layerFound = true;
                    break;
                }
            }

            if(!layerFound)
            {
                return false;
            }
        }

        return true;
    }

    std::vector<const char*> getRequiredExtensions()
    {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if(enableValidationLayers)
        {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }

private:
    GLFWwindow* window;
    VkInstance instance;
};