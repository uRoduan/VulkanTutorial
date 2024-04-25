#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <memory>

#include "DebugMessengerExt.h"
#include "Instance.h"
#include "PhysicalDevice.h"
#include "Device.h"
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
    void InitPhysicalDevice();
    void MainLoop();
    void CleanUp();

private:
    GLFWwindow* m_window;

    std::shared_ptr<Instance> m_pInstance;
    std::shared_ptr<PhysicalDevice> m_pPhysicalDevice;
#ifdef _DEBUG
    std::shared_ptr<DebugMessengerExt> m_debugMessenger;
#endif
};