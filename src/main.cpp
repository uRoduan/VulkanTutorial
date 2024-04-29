// #include "HelloTriangleApplication.hpp"
#include "Application.h"
//
int main() {
    // HelloTriangleApplication app;

    // try
    // {
    //     app.run();
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    //     return EXIT_FAILURE;
    // }


    // return EXIT_SUCCESS;
    Application app;
    app.InitWindow();
    app.InitVulkanInstance();
    app.InitDebugMessenger();
    //app.InitSurface();
    app.InitPhysicalDevice();
    app.InitLogicalDevice();
    app.InitQueue();
    app.InitSwapChain();
    app.MainLoop();
    app.CleanUp();
    
}

