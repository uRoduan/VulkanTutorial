cmake_minimum_required(VERSION 3.10)

project(VulkanTutorial)

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 17)

include_directories($ENV{VK_SDK_PATH}\\Include)
include_directories(external\\glm)
include_directories(external\\glfw-3.3.8.bin.WIN64\\include)

link_directories($ENV{VK_SDK_PATH}\\Lib)
link_directories(external\\glfw-3.3.8.bin.WIN64\\lib-vc2019)

set(LIB_VULKAN $ENV{VK_SDK_PATH}\\Lib\\vulkan-1.lib)
set(SOURCES src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC ${GLM_LIBRARIES} ${GLFW_LIBRARIES} ${LIB_VULKAN})