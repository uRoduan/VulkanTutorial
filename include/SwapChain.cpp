#include "SwapChain.h"

SwapChainSupportDetails SwapChain::QuerySwapChainSupport(VkPhysicalDevice device)
{
    SwapChainSupportDetails details;

    ////This function takes the specified VkPhysicalDevice and VkSurfaceKHR window surface into account when determining the supported capabilities.
    ////All of the support querying functions have these two as first parameters because they are the core components of the swap chain.
    //vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

    //uint32_t formatCount;
    //vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

    //if(formatCount)
    //{
    //    details.formats.resize(formatCount);
    //    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
    //}

    //uint32_t presentModeCount;
    //vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

    //if(presentModeCount)
    //{
    //    details.presentModes.resize(presentModeCount);
    //    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
    //}

    return details;
}