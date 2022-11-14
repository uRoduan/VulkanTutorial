@echo off

set VULKAN_SDK_PATH=%VK_SDK_PATH%
set GLSLC_PATH=%VK_SDK_PATH%\Bin\glslc.exe

echo glslc.exe in: %GLSLC_PATH%

%GLSLC_PATH% shader.vert -o vert.spv
%GLSLC_PATH% shader.frag -o frag.spv