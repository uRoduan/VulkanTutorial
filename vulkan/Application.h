#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <memory>

#include "DebugMessengerExt.h"
#include "Instance.h"
#include "PhysicalDevice.h"
#include "Device.h"
#include "Queue.h"
#include "SwapChain.h"
#include "Macros.h"
#include "VkUtility.h"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;
const int MAX_FRAMES_IN_FLIGHT = 2;

const std::vector<const char*> validationLayers = 
{
    "VK_LAYER_KHRONOS_validation"
};

class Application
{
public:
    Application(){}
    void InitWindow();
    void InitVulkanInstance();
    void InitDebugMessenger();
    //void InitSurface();
    void InitPhysicalDevice();
    void InitLogicalDevice();
    void InitQueue();
    void InitSwapChain();
    void MainLoop();
    void CleanUp();

private:
    GLFWwindow* m_window;
    VkSurfaceKHR m_surface;

    std::shared_ptr<Instance> m_pInstance;
    std::shared_ptr<PhysicalDevice> m_pPhysicalDevice;
    std::shared_ptr<Device> m_pDevice;
    std::shared_ptr<SwapChain> m_pSwapChain;

    std::shared_ptr<Queue> m_queues[(uint32_t)PhysicalDevice::QueueFamily::COUNT];
#ifdef _DEBUG
    std::shared_ptr<DebugMessengerExt> m_debugMessenger;
#endif
};