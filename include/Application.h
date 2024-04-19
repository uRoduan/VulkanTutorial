#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <memory>

#include <Instance.h>
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
    void MainLoop();
    void CleanUp();

private:
    GLFWwindow* m_window;

    std::shared_ptr<Instance> m_instance;
};