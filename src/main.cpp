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
    Application app(true);
    app.InitWindow();
    app.MainLoop();
    app.CleanUp();
    
}

