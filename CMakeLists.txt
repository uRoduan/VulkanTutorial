cmake_minimum_required(VERSION 3.10)

project(VulkanTutorial)

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 20)

set(PROJECT_PATH ${PROJECT_SOURCE_DIR})
ADD_DEFINITIONS( -D_PROJECT_PATH=\"${PROJECT_PATH}\" )

include_directories($ENV{VK_SDK_PATH}\\Include)
include_directories(external\\glm)
include_directories(external\\glfw-3.3.8.bin.WIN64\\include)
include_directories(external)

link_directories($ENV{VK_SDK_PATH}\\Lib)
link_directories(external\\glfw-3.3.8.bin.WIN64\\lib-vc2019)

set(LIB_VULKAN $ENV{VK_SDK_PATH}\\Lib\\vulkan-1.lib)
# set(SOURCES src/main.cpp include/MemoryManager/MemoryBlock.hpp include/MemoryManager/MemoryChunk.hpp
# 	include/stb_image.h include/tiny_obj_loader.h include/HelloTriangleApplication.hpp include/VkUtility.h include/VkUtility.cpp include/Application.h include/Application.cpp
# 	include/Instance.h include/Instance.cpp include/Macros.h)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin)

file(GLOB SOURCES src/*.cpp src/*.h scr/*.hpp)
file(GLOB INCLUDES include/*.cpp include/*.hpp include/*.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${INCLUDES})

target_link_libraries(${PROJECT_NAME} PUBLIC ${GLM_LIBRARIES} glfw3 ${LIB_VULKAN})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)